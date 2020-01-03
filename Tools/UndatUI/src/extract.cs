using System;
using System.IO;
using System.Linq;
using System.Threading;

namespace undat_ui
{
    public class Extractor
    {
        Action<string, int, int> updater;
        Action<string> error;
        Action onSuccess;
        Action onError;

        string masterPath;
        string filesPath;
        string outputPath;
        string[] extractFiles;

        int completedFiles = 0;
        int curFile = 0;
        public int numFiles = 0;

        FO1Dat dat;

        public Thread thread;

        public Extractor(Action<string> error, Action<string, int, int> updater, Action onSuccess, Action onError,
            string masterPath, string filesPath, string outputPath)
        {
            this.updater = updater;
            this.onSuccess = onSuccess;
            this.onError = onError;
            this.error = error;
            this.masterPath = masterPath;
            this.filesPath = filesPath;
            this.outputPath = outputPath + "\\data";
        }

        public void ExtractFiles()
        {
            while (completedFiles < numFiles)
            {
                var f = GetNextFile();
                if (f == null)
                    break; // we are done.

                var ent = f.Split('\\');
                var dir = "";
                foreach (var d in ent)
                {
                    if (d.Contains("."))
                        break;
                    dir += d + "\\";
                    if (!Directory.Exists(this.outputPath + "\\" + dir))
                        Directory.CreateDirectory(this.outputPath + "\\" + dir);
                }

                var file = dat.getFile(f);
                if (file == null)
                    continue;
                File.WriteAllBytes($"{this.outputPath}\\{f}", dat.getData(file));
                
                this.updater(f, completedFiles++, this.numFiles);
            }

            this.updater("All files were extracted.", this.numFiles, this.numFiles);
            this.onSuccess();
        }

        public string GetNextFile()
        {
            var c = curFile++;
            if (c >= numFiles)
                return null;
            return extractFiles[c];
        }

        public string[] ParseExtractFiles()
        {
            var undatFilesPath = this.filesPath;
            if (!File.Exists(undatFilesPath))
            {
                error("Unable to find " + undatFilesPath);
                this.onError();
                return null;
            }

            string[] extractFiles = null;
            try
            {
                extractFiles = File.ReadAllLines(undatFilesPath);
            }
            catch (IOException ex)
            {
                error($"IO exception occured while trying to read {undatFilesPath}: " + ex.Message);
                this.onError();
            }
            catch (UnauthorizedAccessException ex)
            {
                error($"Unauthorized to read {undatFilesPath}: " + ex.Message);
                this.onError();
            }
            catch (Exception ex)
            {
                error($"Exception occured while trying to read {undatFilesPath}: " + ex.Message);
                this.onError();
            }
            this.numFiles = extractFiles?.Count() ?? 0;
            return extractFiles;
        }

        public void Begin()
        {
            this.extractFiles = ParseExtractFiles();
            dat = new FO1Dat();
            var error = dat.Open(masterPath);

            if (error == ReadError.FileDoesntExist)
            {
                this.error("The file you've provided as MASTER.DAT doesn't exist.");
                this.onError();
                return;
            }

            if (error == ReadError.NotValidMasterDat)
            {
                this.error("The file is not a valid MASTER.DAT from Fallout 1.");
                this.onError();
                return;
            }

            if (!Directory.Exists(this.outputPath))
            {
                this.error($"Directory that you've selected as destination: '{this.outputPath}' doesn't exist.");
                this.onError();
                return;
            }

            this.thread = new Thread(new ThreadStart(ExtractFiles));
            this.thread.Start();
        }

    }
}

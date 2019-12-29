using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace undat_ui
{
    public static class Misc
    {
        public static bool FalloutExeInFolder(string folderPath)
        {
            foreach (var file in Directory.GetFiles(folderPath))
            {
                if (Path.GetFileName(file).ToLower() == "fallout2.exe")
                    return true;
            }
            return false;
        }
    }

    public static class Program
    {
        static void MsgError(string error)
            => MessageBox.Show(error, "FO1 DAT extractor", MessageBoxButtons.OK, MessageBoxIcon.Error);
        
        [STAThread]
        static void Main()
        {
            string[] args = Environment.GetCommandLineArgs();
            var parsedArgs = new Dictionary<string, string>();

            string filelist = null;
            string master = null;
            string mod = null;
            if (args.Length != 1)
            {
                var buffer = "";
                var arg = "";
                foreach (var a in args)
                {
                    if (a[0] == '-')
                    {
                        if (buffer != "")
                            parsedArgs[arg] = buffer;
                        arg = a;
                        buffer = "";
                        continue;
                    }
                    if (buffer != "")
                        buffer += " ";
                    buffer += a;
                }
                if (buffer != "")
                    parsedArgs[arg] = buffer;

                if (!parsedArgs.ContainsKey("-m"))
                {
                    MsgError("No path for MASTER.DAT was given.");
                    return;
                }

                if (!parsedArgs.ContainsKey("-l"))
                {
                    MsgError("No path for undat_files.txt was given.");
                    return;
                }

                if (!parsedArgs.ContainsKey("-d"))
                {
                    MsgError("No path for mod directory was given.");
                    return;
                }

                filelist = parsedArgs["-l"];
                master = parsedArgs["-m"];
                mod = parsedArgs["-d"];

                if (!File.Exists(master))
                {
                    MsgError("MASTER.DAT supplied doesn't exist.");
                    return;
                }
                if (!File.Exists(filelist))
                {
                    MsgError("undat_files.txt supplied doesn't exist.");
                    return;
                }

                if (!Directory.Exists(mod))
                {
                    MsgError("mod directory supplied doesn't exist.");
                    return;
                }
            }
            else
            {
                if(Misc.FalloutExeInFolder(Directory.GetCurrentDirectory()))
                    mod = Directory.GetCurrentDirectory();
            }

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new frmMain(filelist, master, mod));
        }
    }
}

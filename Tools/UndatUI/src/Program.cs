using System;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace undat_ui
{
    static class Program
    {
        [DllImport("kernel32.dll")]
        static extern bool AttachConsole(int dwProcessId);
        private const int ATTACH_PARENT_PROCESS = -1;

        [DllImport("kernel32.dll", SetLastError = true)]
        internal static extern int FreeConsole();

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            string[] args = Environment.GetCommandLineArgs();
            if (args.Length == 1)
            {
                Application.EnableVisualStyles();
                Application.SetCompatibleTextRenderingDefault(false);
                Application.Run(new frmMain());
                return;
            }
            AttachConsole(ATTACH_PARENT_PROCESS);

            if (args.Length != 3)
            {
                Console.WriteLine("undat.exe [FO1 directory] [mod directory] []");
                return;
            }

            var master = args[1];
            var mod = args[2];

            if(!File.Exists(master))
            {
                Console.WriteLine("Invalid MASTER.DAT.");
                return;
            }
            if (!Directory.Exists(mod))
            {
                Console.WriteLine("Invalid mod directory.");
                return;
            }
            // Clear line
            Console.Write("\r" + new string(' ', Console.WindowWidth) + "\r");
            var extract = new Extractor((err) =>
            {
                Console.WriteLine("Error: " + err);
            },
            ((currentFile, cur, max) =>
            {
                Console.Write("\r" + new string(' ', Console.WindowWidth) + $"\r[{cur} / {max}] {currentFile}");
            }),
            master,
            mod);
            extract.Begin();
            extract.thread.Join();

            FreeConsole();
            
        }
    }
}

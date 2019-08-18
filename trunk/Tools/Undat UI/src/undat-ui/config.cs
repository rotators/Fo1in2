using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace undat_ui
{
    class Config
    {
        public static int Threads = 1;

        public static void Read()
        {
           foreach(var line in File.ReadAllLines(Directory.GetCurrentDirectory() + "\\config.cfg"))
           {
                var spl = line.Split('=');
                if (spl[0] == "threads")
                    Config.Threads = int.Parse(spl[1]);
           }
        }

    }
}

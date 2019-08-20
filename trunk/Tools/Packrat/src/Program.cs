using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Packrat
{
    class Program
    {
        static void Main(string[] args)
        {
            //var file = DatFile.FromFile(@"D:\Fallout\dev\Fo1Port\trunk\Fallout2\Fallout1Port\data\art\inven\CAP2.FRM", @"art\inven", true);
            //var file2 = DatFile.FromFile(@"D:\Fallout\dev\Fo1Port\trunk\Fallout2\Fallout1Port\data\art\inven\zipgun.FRM", @"art\inven", true);
            //Dat.CreateDat(Directory.GetCurrentDirectory() + "\\test.dat", new List<DatFile> { file, file2});
            Script.Run("script.pack");
            Console.ReadKey();
        }
    }
}

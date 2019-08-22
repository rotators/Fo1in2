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
            System.Threading.Thread.CurrentThread.CurrentCulture = System.Globalization.CultureInfo.CreateSpecificCulture("en-US");
            System.Threading.Thread.CurrentThread.CurrentUICulture = System.Threading.Thread.CurrentThread.CurrentCulture;

            if( args.Length > 0 && args[0].Length > 0 )
            {
              if( File.Exists( args[0] ))
                Script.Run( args[0] );
              else
              {
                Console.WriteLine( $"Cannot find packing script ({args[0]})" );
                return;
              }
            }
            else if( File.Exists( "script.pack" ))
              Script.Run("script.pack");
            else if( File.Exists( "script.packrat" ))
              Script.Run("script.packrat");
            else
            {
              Console.WriteLine( "Cannot find packing script (script.pack or script.packrat) and no filename provided" );
              return;
            }

            // should be ReadKey() ... which throws System.InvalidOperationException in git-bash :/
            Console.Read();
        }
    }
}

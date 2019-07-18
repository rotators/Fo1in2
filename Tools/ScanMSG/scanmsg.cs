// Wipe/Rotators

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;

namespace scanmsg
{
    class FalloutMsg
    {
        public enum LoadStatus
        {
            OK,
            FileDoesNotExists,
            FileIsEmpty,
            ExtraBracket,
            InvalidId,
            DuplicatedId,
            TextTooLong,
        }

        class MsgEntry
        {
            public string Sound;
            public string Text;

            public MsgEntry( string sound, string text )
            {
                Sound = sound;
                Text = text;
            }
        }

        Dictionary<uint,MsgEntry> Msg = new Dictionary<uint,MsgEntry>();
        uint MsgLast = 0;

        public LoadStatus Load( string filename )
        {
            if( !File.Exists( filename ) )
                return LoadStatus.FileDoesNotExists;

            string[] lines = File.ReadAllLines( filename );
            if( lines.Length == 0 )
            {
                scanmsg.Report( "file is empty [" + filename + "]" );
                return LoadStatus.FileIsEmpty;
            }

            //bool blank = File.ReadAllText( filename ).Last() == '\n';

            uint number = 0;
            bool multi = false;
            //string last = "";

            foreach( string fline in lines )
            {
                number++;
                string line = fline.Replace( "\t", " " );

                LoadStatus status = LoadStatus.OK;
                string report = "";
                if( !LoadLine( line, ref multi, ref status, ref report ) )
                {
                    scanmsg.Report( line );
                    scanmsg.Report( report + " [" + filename + ":" + number + "]" );
                }

                //last = line;
            }

            //if( !blank )
            //{
            //    scanmsg.Report( last );
            //    scanmsg.Report( new string( '-', last.Length ) + "^ blank line required [" + filename + ":" + number + "]" );
            //}

            return LoadStatus.OK;
        }

        bool LoadLine( string line, ref bool multi, ref LoadStatus status, ref string report )
        {
            Match match;
            if( multi )
            {
                match = Regex.Match( line, "^(.*)}(.*)$" );
                if( match.Success )
                {
                    multi = false;
                    string stripped = match.Groups[1].Value + " " + match.Groups[2].Value;
                    if( !CheckBrackets( stripped, ref report, true ) )
                    {
                        status = LoadStatus.ExtraBracket;
                        return false;
                    }

                    int len = Msg[MsgLast].Text.Length + match.Groups[1].Value.Length;
                    if( len > 1024 )
                    {
                        report = new string( '-', 1024 - Msg[MsgLast].Text.Length ) + "^ text too long [multiline]";
                        status = LoadStatus.TextTooLong;
                        return false;
                    }
                    Msg[MsgLast].Text += match.Groups[1].Value;
                }
                else
                    Msg[MsgLast].Text += line;
            }
            else
            {
                bool process = false;
                string stripped = "";

                match = Regex.Match( line, "^(.*?){(.*)}{(.*)}{(.*)}(.*?)$" );
                if( !process && match.Success )
                {
                    process = true;
                    stripped = match.Groups[1].Value + " " + match.Groups[2].Value + "  " + match.Groups[3].Value + "  " + match.Groups[4].Value + " " + match.Groups[5].Value;
                }

                match = Regex.Match( line, "^(.*?){(.*)}{(.*)}{(.*)$" );
                if( !process && match.Success )
                {
                    process = multi = true;
                    stripped = match.Groups[1].Value + " " + match.Groups[2].Value + "  " + match.Groups[3].Value + "  " + match.Groups[4].Value;
                }

                if( !process )
                    return true;

                if( !CheckBrackets( stripped, ref report ) )
                {
                    status = LoadStatus.ExtraBracket;
                    return false;
                }

                uint id = CheckId( match.Groups[2], ref report );
                if( id == uint.MaxValue )
                {
                    status = LoadStatus.InvalidId;
                    return false;
                }

                if( match.Groups[4].Value.Length > 1024 )
                {
                    report = new string( '-', match.Groups[4].Index + 1024 ) + "^ text too long";
                    status = LoadStatus.TextTooLong;
                    return false;
                }

                if( id > 0 && Msg.ContainsKey( id ) )
                {
                    report = new string( '-', match.Groups[2].Index ) + "^ id already in use";
                    status = LoadStatus.DuplicatedId;
                    return false;
                }
                else
                {
                    Msg[id] = new MsgEntry( match.Groups[3].Value, match.Groups[4].Value );
                    MsgLast = id;
                }
            }
            return true;
        }

        bool CheckBrackets( string stripped, ref string report, bool multi = false )
        {
            Match brackets = Regex.Match( stripped, "({|})" );
            if( brackets.Success )
            {
                if( brackets.Groups[1].Index > 0 )
                    report = new string( '-', brackets.Groups[1].Index ) + "^";
                else
                    report = "^";

                report += " bracket not allowed here";
                if( multi )
                    report += " [multiline]";
                return false;
            }

            return true;
        }

        uint CheckId( Group group, ref string report )
        {
            uint id = uint.MaxValue;

            if( group.Value.Length == 0 ||
                !Regex.Match( group.Value, "^[0-9]+$" ).Success ||
                !uint.TryParse( group.Value, out id ) )
            {
                report = new string( '-', group.Index ) + "^ invalid id";
                return uint.MaxValue;
            }

            return id;
        }
    }

    class scanmsg
    {
        static string ReportFile = "scanmsg.txt";

        static void Main( string[] args )
        {
            Console.Write( "Scanning files..." );

            if( File.Exists( ReportFile ) )
                File.Delete( ReportFile );


            string[] files = Directory.GetFiles( ".", "*.msg", SearchOption.AllDirectories ).OrderBy( f => f ).ToArray();
            Console.WriteLine( " {0} found", files.Length );

            foreach( string file in files )
            {
                FalloutMsg msg = new FalloutMsg();
                msg.Load( file.TrimStart( '.', '/', '\\' ) );
            }
        }

        public static void Report( string report = "" )
        {
            Console.WriteLine( report );
            File.AppendAllText( ReportFile, report + Environment.NewLine );
        }
    }
}

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Packrat
{
    enum Operation
    {
        Nop,
        Comment, // Ignore
        Assign,  // Assign variable
        Pack,    // Pack function, fetch files accordingly to pattern and load into memory.
        Output,  // Output to DAT function
        Echo     // Write to console.
    }

    class OpCall
    {
        public Operation op;
        public List<string> args = new List<string>();
    }

    // Best "scripting language" ever, even better than the fallout one...
    class Script
    {
        readonly static string[] ValidFunctions = new string[] { "echo", "pack", "output" };

        private static OpCall ParseLine(string line, int lineNum)
        {
            string buffer="";

            OpCall call = new OpCall() { op=Operation.Nop };

            for(var i=0;i<line.Length;i++)
            {
                var c = line[i];
                if (c == ' ') // ignore space
                    continue;

                if(c == '"' && call.op == Operation.Assign)
                {
                    if (line.IndexOf('"', i) == -1)
                    {
                        Console.WriteLine($"Error on line {lineNum}, unclosed string for assigned value for variable.");
                        break;
                    }
                    else
                    {
                        call.args.Add(line.Substring(i+1, line.IndexOf('"', i+1) - i - 1));
                        break;
                    }
                }

                if(c == '#')
                    break;

                // Function call
                if (c == '(' && call.op == Operation.Nop)
                {
                    if(!Script.ValidFunctions.Contains(buffer))
                    {
                        Console.WriteLine($"Error on line {lineNum}, '{buffer}' is not a valid function.");
                        break;
                    }

                    if(line.IndexOf(')') == -1)
                    {
                        Console.WriteLine($"Error on line {lineNum}, '{buffer}' is not closed properly.");
                    }

                    if (buffer == "echo") call.op = Operation.Echo;
                    if (buffer == "pack") call.op = Operation.Pack;
                    if (buffer == "output") call.op = Operation.Output;

                    var args = line.Substring(line.IndexOf('(')+1, line.IndexOf(')') - line.IndexOf('(') - 1);
                    foreach(var arg in args.Split(','))
                    {
                        var parsed = arg.Trim();
                        if (parsed == "true" || parsed == "false")
                        {
                            call.args.Add(parsed);
                        }
                        else if (arg.IndexOf('"') != -1)
                        {
                            parsed = parsed.Substring(1, parsed.LastIndexOf('"') - 1);
                            call.args.Add(parsed);
                        }
                        else
                        {
                            Console.WriteLine($"Error on line {lineNum}, invalid argument type.");
                            break;
                        }
                    }
                }

                if (c == '=' && call.op == Operation.Nop)
                {
                    call.op = Operation.Assign;
                    call.args.Add(buffer); // variable name
                    buffer = "";
                }
                buffer += c;
            }

            return call;
        }

        static Dictionary<string, string> Variables = new Dictionary<string, string>();

        static List<DatFile> files = new List<DatFile>();
        public static void Run(string script)
        {
            var lines = File.ReadAllLines(script);
            var i = 1;
            var calls = new List<OpCall>();
            foreach(var l in lines)
            {
                calls.Add(ParseLine(l, i++));
            }

            calls = calls.Where(x => x.op != Operation.Nop).ToList();
            foreach(var c in calls)
            {
                for(var x=0;x<c.args.Count;x++)
                {
                    foreach(var kvp in Variables)
                    {
                        if (c.args[x].Contains("%" + kvp.Key + "%"))
                            c.args[x] = c.args[x].Replace("%" + kvp.Key + "%", kvp.Value);
                    }
                }

                if (c.op == Operation.Assign)
                {
                    Variables[c.args[0]] = c.args[1];
                }

                if (c.op == Operation.Echo)
                {
                    Console.WriteLine(c.args[0]);
                }

                if (c.op == Operation.Pack)
                {                   
                    var dir = c.args[0];
                    var datPath = c.args[1];
                    var compress = c.args[2] == "true";

                    var pattern = c.args[0].Split('\\').Last();
                    if (pattern.IndexOf('*') == -1 && pattern.IndexOf('.') == -1) // dir?
                        pattern = "";
                    else
                        dir = dir.Substring(0, dir.LastIndexOf('\\'));

                    foreach(var f in Directory.GetFiles(dir, pattern))
                    {
                        Console.WriteLine($"Adding {f} to {datPath}");
                        files.Add(DatFile.FromFile(f, datPath, compress));
                    }
                }

                if (c.op == Operation.Output)
                {
                    Console.WriteLine($"Writing {c.args[0]}...");
                    Dat.CreateDat(c.args[0], files);
                    files.Clear();
                }
            }

        }

    }
}

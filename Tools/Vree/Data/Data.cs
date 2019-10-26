using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Threading.Tasks;

namespace Vree.Data
{
    // https://docs.microsoft.com/en-us/cpp/cpp/argument-passing-and-naming-conventions?view=vs-2019
    public enum CallingConvention
    {
        cdecl,      // Caller cleans stack, parameters on stack, in reverse order (right to left).
        stdcall,    // Callee cleans stack, parameters on stack, in reverse order (right to left)
        fastcall,   // Callee cleans stack, Arg 1 in ECX, Arg 2 in EDX, rest on stack in reverse order (right to left). 
        thiscall,   //
        vectorcall, //
        watcom      // Arg 1 in EAX, 2 in EDX, 3 in EBX, 4 in ECX, rest on stack in left to right order.
    }

    [Serializable]
    public class Argument
    {
        public Enum Enum;
        public DataType Type;
        public string Name;

        public string String
        {
            get
            {
                string def = Enum != null ? Enum.Name : Type.String;
                return def + " " + Name;
            }
        }
    }

    [Serializable]
    public class Function
    {
        public ReturnVariable ReturnType;
        public uint Offset;
        public string Name;
        public List<Argument> Arguments;
        public CallingConvention Calling;
        public string Comment;
        public bool Implemented; // Has been reimplemented.
        public string Definition
        {
            get
            {
                string retString = ReturnType == null ? "void" : ReturnType.String;
                string args = Arguments == null ? "" : string.Join(", ", Arguments.Select(x => x.String).ToArray());
                return $"{retString} {Name}({args})";
            }
        }
    }
    [Serializable]
    public class ReturnVariable
    {
        public bool IsArray() => Length > 1;
        public bool Pointer;
        public UInt16 Length;
        public DataType Type;

        public string LenStr
        {
            get
            {
                if (Length == 1 || Length == 0)
                    return "";
                if (Length == UInt16.MaxValue) // This probably a bad way to represent []
                    return "[]";
                return $"[{Length}]";
            }
        }
        public string String
        {
            get
            {
                return Type.String + LenStr+(Pointer?"*":"");
            }
        }
    }

    [Serializable]
    public class GlobalVariable
    {
        public bool IsArray() => Length > 1;
        public bool Pointer;
        public UInt16 Length;
        public uint Offset;
        public string Name;
        public DataType Type;
        public string Comment;
        public void SetBasicType(BasicType type)
        {
            if (Type == null)
                Type = new DataType();
            Type.BasicType = type;
            Type.IsBasicType = true;
        }
        public string String
        {
            get
            {
                var t = Type == null ? "void*" : Type.String;
                return t + (Length > 0 ? "[]" : "") + (Pointer ? "*" : "") + " " + Name;
            }
        }
    }

    [Serializable]
    public class VreeDB
    {
        public List<Function> Functions;
        public List<GlobalVariable> Variables;
        public List<DataType> Types;
        public List<Enum> Enums;

        public static string FindPath()
        {
            var startDir = Environment.CurrentDirectory;
            var dir = startDir;
            while (true)
            {
                if (dir.Length == 3)
                    return null;
                dir = Path.GetFullPath(dir + "\\..");

                if (File.Exists(dir + "/Readme.md") && Directory.Exists(dir + "/Fallout2")
                    && Directory.Exists(dir + "/Resources") && Directory.Exists(dir + "/Tools"))
                    break;
            }
            return Path.GetFullPath(dir + "/Reversing/fo2_vree.db");
        }

        public static VreeDB Load(string filename)
        {
            VreeDB db = null;
            using (var fileStream = new FileStream(filename, FileMode.Open, FileAccess.Read))
            {

                //create a BinaryFormatter and deserialize the object
                BinaryFormatter formatter = new BinaryFormatter();
                db = (VreeDB)formatter.Deserialize(fileStream);
                fileStream.Close();
            }
            return db;
        }
        public bool Save(string filename)
        {
            var noext = Path.GetFileNameWithoutExtension(filename);
            var dir = Path.GetDirectoryName(filename);
            if (File.Exists(dir + "\\" + noext + ".bak"))
                File.Delete(dir + "\\" + noext + ".bak");

            

            if (File.Exists(filename))
                File.Move(filename, dir + "\\" + noext+".bak");

            BinaryFormatter formatter = new BinaryFormatter();
            //formatter.Binder = new CustomizedBinder();
            FileStream fileStream = new FileStream(filename, FileMode.Create);
            formatter.Serialize(fileStream, this);
            return true;
        }

    }
}

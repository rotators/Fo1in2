using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Vree.Data
{
    
    public static class TypeExt
    {
        public static string GetExportType(this BasicType type, ExportLanguage language)
        {
            // Assumes MSVC++
            /*if(language == ExportLanguage.cpp)
            {
                switch(type)
                {
                    //case BasicType.
                }
            }*/
            return "";
        }

        public static IEnumerable<BasicType> AllBasicTypes(this BasicType type)
        {
            yield return BasicType.FLOAT;
            yield return BasicType.INT8;
            yield return BasicType.INT16;
            yield return BasicType.INT32;
            yield return BasicType.INT64;
            yield return BasicType.UINT8;
            yield return BasicType.UINT16;
            yield return BasicType.UINT32;
            yield return BasicType.UINT64;
            yield return BasicType.CHARP;
            yield return BasicType.BOOL;
            yield return BasicType.VOID;
        }
        public static string GetBasicTypeString(this BasicType type)
        {
            switch(type)
            {
                case BasicType.FLOAT: return "float";
                case BasicType.INT8: return "int8";
                case BasicType.INT16: return "int16";
                case BasicType.INT32: return "int32";
                case BasicType.INT64: return "int64";
                case BasicType.UINT8: return "uint8";
                case BasicType.UINT16: return "uint16";
                case BasicType.UINT32: return "uint32";
                case BasicType.UINT64: return "uint64";
                case BasicType.CHARP: return "char*";
                case BasicType.BOOL: return "bool";
                case BasicType.VOID: return "void";
                default: throw new Exception("Unable to find string for type: " + type);
            }
        }
    }

    public enum ExportLanguage
    {
        cpp,
        csharp
    }

    // Uppercase to avoid conflict with keywords in C#
    public enum BasicType {
        VOID,
        BOOL,
        CHARP,  // char*
        INT8, 
        UINT8,
        INT16, 
        UINT16, 
        INT32,
        UINT32,
        INT64,
        UINT64,
        FLOAT  // 4 bytes
    }

    [Serializable]
    public class Enum
    {
        public bool DisplayAsHex;
        public BasicType Type;
        public string Name;
    }

    [Serializable]
    public class Field
    {
        DataType Type;
        UInt16 Offset; // Offset within the datastructure in bytes.
        string Name;
    }

    [Serializable]
    public class DataType
    {
        public bool IsBasicType;
        public BasicType BasicType;
        public string CustomName;
        public List<Field> Fields;
        public string String
        {
            get
            {
                if (IsBasicType)
                    return BasicType.GetBasicTypeString();
                return CustomName;
            }
        }
    }
}

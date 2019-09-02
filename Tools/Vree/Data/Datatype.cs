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
        INT8, 
        UINT8,  // char*
        INT16, 
        UINT16, 
        INT32,
        UINT32,
        INT64,
        UINT64,
        FLOAT  // 4 bytes
    }

    [Serializable]
    class Enum
    {
        public bool DisplayAsHex;
        public BasicType Type;
        public string Name;
    }

    [Serializable]
    class Field
    {
        DataType Type;
        UInt16 Offset; // Offset within the datastructure in bytes.
        string Name;
    }

    [Serializable]
    class DataType
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

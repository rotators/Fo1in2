using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;




namespace Overseer
{
    public class PathNode
    {
        public string path;
        public int datPtr;
        public long isDat;
        public int nextPtr;
    }

    public class ScriptListInfo
    {
        public string fileName;
        public long numLocalVars;
    }

    public class Memory
    {
        const int PROCESS_VM_READ = 0x10;

        [DllImport("kernel32", SetLastError = true)]
        public static extern IntPtr OpenProcess(
                    int dwDesiredAccess,
                    IntPtr bInheritHandle,
                    IntPtr dwProcessId
                    );

        [DllImport("kernel32.dll")]
        public static extern int ReadProcessMemory(
        IntPtr hProcess,
        int lpBase,
        ref byte lpBuffer,
        int nSize,
        int lpNumberOfBytesRead
        );

        Process process;
        IntPtr handle;

        public Memory(int pid)
        {
            this.process = Process.GetProcessById(pid);
            this.handle = OpenProcess(PROCESS_VM_READ, IntPtr.Zero, new IntPtr(process.Id));
            
            //int test = 0;
            //ReadProcessMemory(this.handle, 0x51DE2C, ref test, 1, 0);
        }

        public byte[] ReadBytes(int offset, int bytes)
        {
            byte[] buffer = new byte[bytes];
            byte buf=0;
            //int bytesRead = 0;
            for (int i = 0; i < bytes; i++)
            {
                ReadProcessMemory(this.handle, offset+i, ref buf, 1, 0);
                buffer[i] = buf;
            }
            return buffer;
        }

        public byte ReadByte(int offset)
        {
            return ReadBytes(offset, 1)[0];
        }

        public short ReadInt16(int offset)
        {
            return BitConverter.ToInt16(ReadBytes(offset, 2), 0);
        }

        public int ReadInt(int offset)
        {
            return BitConverter.ToInt32(ReadBytes(offset, 4), 0);
        }
        public long ReadInt64(int offset)
        {
            return BitConverter.ToInt64(ReadBytes(offset, 8), 0);
        }

        public ScriptListInfo ReadScriptListInfo(int offset)
        {
            var name = Encoding.ASCII.GetString(ReadBytes(offset, 16));
            if (name.IndexOf('\0') == -1)
                return null;
            name = name.Substring(0, name.IndexOf('\0'));
            var num = ReadInt(offset + 16);
            return new ScriptListInfo()
            {
                fileName = name,
                numLocalVars = num
            };
        }

        public PathNode ReadPathNode(int offset)
        {
            var pn = new PathNode();
            int curOffset = offset;
            pn.path= ReadString(curOffset, out curOffset);
            pn.datPtr = ReadInt(curOffset);
            curOffset += 4;
            pn.isDat = ReadByte(curOffset);
            curOffset += 8;
            pn.nextPtr = ReadInt(curOffset);
            return pn;
        }

        public string ReadString(int offset, out int endOffset)
        {
            StringBuilder sb = new StringBuilder();
            byte buf = 1;
            while((char)buf != '\0')
            {
                ReadProcessMemory(this.handle, offset++, ref buf, 1, 0);
                sb.Append((char)buf);
            }
            endOffset = offset;
            return sb.ToString();
        }

        public bool ReadBool(int offset)
        {
            return BitConverter.ToBoolean(ReadBytes(offset, 1),0);
        }
    }
}

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Overseer
{
    public class Pointer<T> where T : IParsable<T>
    {
        int ptr;
        MemoryReader mem;

        public Pointer(int offset, MemoryReader mem)
        {
            this.ptr = offset;
            this.mem = mem;
        }

        public bool IsValid() { return ptr != 0; }
        private T CallParse()
        {
            var t = typeof(T);
            return t.GetMethod("Parse", BindingFlags.Public | BindingFlags.Static).Invoke(null, new object[] { this.mem }) as T;
        }
        public T Read()
        {
            this.mem.offset = this.ptr;
            return this.CallParse();
        }
        public T Dereference()
        {
            this.mem.offset = this.mem.Dereference(ptr);
            return this.CallParse();
        }
    }

    // Reads bytes and advances offset.
    public class MemoryReader
    {
        public int offset;
        protected Memory mem;
        public MemoryReader(Memory mem)
        {
            this.mem = mem;
        }

        /**
         * Dereference a pointer at offset and set it, doesn't advance offset.
         */
        public int Dereference(int offset)
        {
            this.offset = mem.ReadInt32(offset);
            return this.offset;
        }

        public bool ValidatePointer(int offset)
        {
            return mem.ReadInt32(offset) != 0;
        }

        public byte[] ReadBytes(int bytes)
        {
            var b = mem.ReadBytes(offset, bytes);
            this.offset += bytes;
            return b;
        }
        public byte ReadByte()  {
            return mem.ReadByte(offset++);
        }

        public short ReadInt16()
        {
            var i = mem.ReadInt16(offset);
            this.offset += 2;
            return i;
        }

        public int ReadInt32()
        {
            var i = mem.ReadInt32(offset);
            this.offset += 4;
            return i;
        }
        public long ReadInt64()
        {
            var l = mem.ReadInt64(offset);
            this.offset += 8;
            return l;
        }

        public string ReadStringPtr()
        {
            var s = mem.ReadString(mem.ReadInt32(offset), out int _);
            this.offset += 4;
            return s;
        }
        public string ReadString(int? len)
        {
            if (len.HasValue)
            {
                var st = mem.ReadStringLen(offset, len.Value);
                offset += len.Value;
                return st;
            }

            int end;
            string s = mem.ReadString(offset, out end);
            this.offset = end;
            return s;
        }
    }

    public class Memory
    {
        const int PROCESS_VM_OPERATION = 0x08;
        const int PROCESS_VM_READ = 0x10;
        const int PROCESS_VM_WRITE = 0x20;


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

        IntPtr handle;
        public Memory(Process process)
        {
            this.handle = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_READ, IntPtr.Zero, new IntPtr(process.Id));
        }

        public byte[] ReadBytes(int offset, int bytes)
        {
            byte[] buffer = new byte[bytes];
            byte buf = 0;
            for (int i = 0; i < bytes; i++)
            {
                ReadProcessMemory(this.handle, offset + i, ref buf, 1, 0);
                buffer[i] = buf;
            }
            return buffer;
        }

        public string ReadStringLen(int offset, int len)
        {
            StringBuilder sb = new StringBuilder();
            byte buf = 1;
            for(int i=0;i<len;i++)
            {
                ReadProcessMemory(this.handle, offset+i, ref buf, 1, 0);
                sb.Append((char)buf);
            }
            return sb.ToString();
        }
        public string ReadString(int offset, out int endOffset)
        {
            StringBuilder sb = new StringBuilder();
            byte buf = 1;
            while ((char)buf != '\0')
            {
                ReadProcessMemory(this.handle, offset++, ref buf, 1, 0);
                sb.Append((char)buf);
            }
            endOffset = offset;
            return sb.ToString();
        }

        public bool ReadBool(int offset)
        {
            return BitConverter.ToBoolean(ReadBytes(offset, 1), 0);
        }

        public byte ReadByte(int offset)
        {
            return ReadBytes(offset, 1)[0];
        }

        public short ReadInt16(int offset)
        {
            return BitConverter.ToInt16(ReadBytes(offset, 2), 0);
        }

        public int ReadInt32(int offset)
        {
            return BitConverter.ToInt32(ReadBytes(offset, 4), 0);
        }
        public long ReadInt64(int offset)
        {
            return BitConverter.ToInt64(ReadBytes(offset, 8), 0);
        }
    }
}

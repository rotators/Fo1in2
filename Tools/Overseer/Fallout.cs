using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Overseer
{
    public class Global<T>
    {
        public int offset;
        public T value;
        public string HexOffset => offset.ToString("x");
    }

    public static class Engine
    {
        static Memory mem;
        static MemoryReader reader;
        static FalloutMemory fmem;

        static Process process;

        // TODO: remove?
        public static Memory Memory => mem;
        public static MemoryReader MemoryReader => reader;
        public static MessageList ReadMessageList(int offset)
            => fmem.ReadMessageList(offset);

        private static Window getWindow(int id)
        {
            id = id << 2;
            var edx = mem.ReadInt32(id + 0x6ADD90);
            var offset = mem.ReadInt32(edx * 4 + 0x6ADE58);
            reader.offset = offset;
            return Window.Parse(reader);
        }

        public static List<Window> GetWindows()
        {
            List<Window> windows = new List<Window>();
            for (var i = 0; i < 25; i++)
            {
                var w = Engine.getWindow(i);
                if (w.id == i)
                    windows.Add(w);
                else
                    break;
            }
            return windows;
        }

        public static IEnumerable<PathNode> ReadPaths()
            => fmem.ReadPaths();

        public static bool AttachToFallout()
        {
            var fallout2 = Process.GetProcessesByName("Fallout2");
            if (fallout2.Length == 0)
                return false;

            if (fallout2.Length > 0)
            {
                Engine.process = fallout2[0];
                Engine.mem = new Memory(Engine.process);
                Engine.reader = new MemoryReader(mem);
                Engine.fmem = new FalloutMemory(reader);
            }

            Globals.Init(mem);

            return true;
        }
    }

    public static class Globals
    {
        static Memory mem;
        public static void Init(Memory mem) {
            Globals.mem = mem;
        }

        // TODO: Generate with script.
        public static Global<byte> WorldPosX => Byte(0x672E0C);
        public static Global<byte> WorldPosY => Byte(0x672E10);
        public static Global<byte> PlayerLevel => Byte(0x6681B0);
        public static Global<short> MouseX => Int16(0x6AC7A8);
        public static Global<short> MouseY => Int16(0x6AC7A4);
        public static Global<string> PlayerName => CString(0x56D75C);

        private static Global<string> CString(int offset) => new Global<string> { offset = offset, value = mem.ReadString(offset, out int _) };
        private static Global<short> Int16(int offset) => new Global<short> { offset = offset, value = mem.ReadInt16(offset) };
        private static Global<int> Int32(int offset) => new Global<int> { offset = offset, value = mem.ReadInt32(offset) };
        private static Global<byte> Byte(int offset) => new Global<byte> { offset = offset, value = mem.ReadByte(offset) };
        private static Global<bool> Bool(int offset) => new Global<bool> { offset = offset, value = mem.ReadBool(offset) };

    }

    public abstract class IParsable<T>
    {
        public static T Parse(MemoryReader mem) { return default(T); }
    }

    public class Button
    {
        public int baseOffset;
        public int id;
        public int flag;
        public int unk;
        public int unk2;
        public int unk3;
        public int unk4;
        public int nextButton;
    }

    public class Window : IParsable<Window>
    {
        public int id;
        public int offset;
        public int flags;
        public int left; 
        public int top;  
        public int right;
        public int bottom;
        public int clearColor;
        public int unknown;
        public int unknown2;
        public int unknown3;
        public int unknown4;
        public byte surface;
        public int buttonPtr;

        public IEnumerable<Button> GetButtons(Memory mem, int unknownOff)
        {
            var off = this.buttonPtr;
            var nextButton = 0;
            do
            {

                var id = mem.ReadInt32(off);
                var flags = mem.ReadInt32(off + 4);
                var unk = mem.ReadInt32(off + unknownOff + 8);
                var unk2 = mem.ReadInt32(off + unknownOff + 12);
                var unk3 = mem.ReadInt32(off + unknownOff + 16);
                var unk4 = mem.ReadInt32(off + unknownOff + 20);
                var somePtr = mem.ReadInt32(off + 128);
                nextButton = mem.ReadInt32(off + 120);
                yield return new Button()
                {
                    baseOffset = off,
                    id = id,
                    unk = unk,
                    unk2 = unk2,
                    unk3 = unk3,
                    unk4 = unk4,
                    flag = flags
                };
                off = nextButton;
            } while (nextButton != 0);
        }

        public new static Window Parse(MemoryReader mem)
        {
            return new Window()
            {
                offset = mem.offset,
                id = mem.ReadInt32(),
                flags = mem.ReadInt32(),
                left = mem.ReadInt32(),
                top = mem.ReadInt32(),
                right = mem.ReadInt32(),
                bottom = mem.ReadInt32(),
                clearColor = mem.ReadInt32(),
                unknown = mem.ReadInt32(),
                unknown2 = mem.ReadInt32(),
                surface = (byte)mem.ReadInt32(),
                unknown3 = mem.ReadInt32(),
                unknown4 = mem.ReadInt32(),
                buttonPtr = mem.ReadInt32(),
            };
        }
    }

    public class PathNode : IParsable<PathNode>
    {
        public string path;
        public Pointer<DatArchive> datArchive;
        public long isDat;
        public Pointer<PathNode> nextPtr;

        public new static PathNode Parse(MemoryReader mem)
        {
            return new PathNode()
            {
                path = mem.ReadStringPtr(),
                datArchive = new Pointer<DatArchive>(mem.ReadInt32(), mem),
                isDat = mem.ReadInt32(),
                nextPtr = new Pointer<PathNode>(mem.ReadInt32(), mem),
            };
        }
    }

    public class ScriptListInfo
    {
        public string fileName;
        public long numLocalVars;
    }

    public class MessageNode
    {
        public int number;
        public int flags;
        public string audio;
        public string message;
    }

    public class DatFile : IParsable<DatFile>
    {
        public string path;
        public bool compressed;
        public int size;
        public int packedSize;
        public int offset;

        public new static DatFile Parse(MemoryReader mem)
        {
            return new DatFile()
            {
                path = mem.ReadStringPtr(),
                compressed = mem.ReadInt32() == 0x01,
                size = mem.ReadInt32(),
                packedSize = mem.ReadInt32(),
                offset = mem.ReadInt32()
            };
        }
    }

    public class DatArchive : IParsable<DatArchive>
    {
        public string Name;
        public int unknown;
        public int numFiles;
        public Pointer<DatFile> FirstFilePtr;

        public IEnumerable<DatFile> GetFiles()
        {
            yield return FirstFilePtr.Read();
            for (var i = 0; i < numFiles - 1; i++)
            {
                yield return DatFile.Parse(Engine.MemoryReader);
            }
        }

        public new static DatArchive Parse(MemoryReader mem)
        {
            return new DatArchive()
            {
                Name = mem.ReadStringPtr(),
                unknown = mem.ReadInt32(),
                numFiles = mem.ReadInt32(),
                FirstFilePtr = new Pointer<DatFile>(mem.ReadInt32(), mem),
            };
        }
    }

    public class MessageList
    {
        public long numMsgs;
        public List<MessageNode> nodes;
    }

    public class FalloutMemory
    {
        MemoryReader reader;
        public FalloutMemory(MemoryReader reader)
        {
            this.reader = reader;
        }

        public MessageList ReadMessageList(int offset)
        {
            this.reader.offset = offset;
            var m = new MessageList();
            m.nodes = new List<MessageNode>();
            m.numMsgs = this.ReadInt32();
            ReadPointer(this.reader.offset);

            for (var i = 0; i < m.numMsgs; i++)
                m.nodes.Add(ReadMessageNode());
            return m;
        }

        public MessageNode ReadMessageNode()
        {
            return new MessageNode()
            {
                number = ReadInt32(),
                flags = ReadInt32(),
                audio = ReadStringPtr(),
                message = ReadStringPtr()
            };
        }

        byte[] ReadBytes(int num) { return this.reader.ReadBytes(num); }
        Int32 ReadPointer(int offset) { return this.reader.Dereference(offset); }
        Int16 ReadInt16() { return this.reader.ReadInt16(); }
        Int32 ReadInt32() { return this.reader.ReadInt32(); }
        Int64 ReadInt64() { return this.reader.ReadInt64(); }

        string ReadStringPtr()
        {
            return this.reader.ReadStringPtr();
        }
        string ReadString(int? len = null)
        {
            string s = this.reader.ReadString(len);
            if (s.IndexOf('\0') == -1)
                return null;
            s = s.Substring(0, s.IndexOf('\0'));
            return s;
        }

        public IEnumerable<PathNode> ReadPaths()
        {
            var n = new Pointer<PathNode>(0x6B24D0, this.reader).Dereference();
            while (n.nextPtr.IsValid())
            {
                yield return n;
                n = n.nextPtr.Read();
            }
        }

        public IEnumerable<ScriptListInfo> ReadScriptList()
        {
            reader.Dereference(0x51C7C8); // dereference pointer and set the offset.
            ScriptListInfo scriptInfo = null;
            do
            {
                scriptInfo = ReadScriptListInfo();
                if (scriptInfo != null)
                    yield return scriptInfo;
            } while (scriptInfo != null);
        }

        public ScriptListInfo ReadScriptListInfo()
        {
            var name = ReadString(16);
            var num = ReadInt32();
            if (num < 0)
                return null;

            return new ScriptListInfo()
            {
                fileName = name,
                numLocalVars = num
            };
        }
    }
}

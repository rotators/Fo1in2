using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace undat_ui
{
    // Implemented by following https://falloutmods.fandom.com/wiki/DAT_file_format#Fallout_1_LZSS_uncompression_algorithm
    // https://en.wikipedia.org/wiki/Lempel-Ziv-Storer-Szymanski
    // https://web.archive.org/web/20160110174426/https://oku.edu.mie-u.ac.jp/~okumura/compression/history.html
    class FO1LZSS
    {
        int uncompressedSize;
        BinaryBigEndian stream;

        readonly short DICT_SIZE = 4096;
        readonly short MIN_MATCH = 3;
        readonly short MAX_MATCH = 18;

        byte[] output;
        byte[] dictionary;

        short N;    // number of bytes to read
        short NR;   // bytes read from last block header
        short DO = 0; // dictionary offset - for reading
        short DI;   // dictionary index - for writing
        int OI = 0; // output index, used for writing to the output array.
        int L;      // match length
        byte FL;    // Flags indicating the compression status of up to 8 next characters.

        public FO1LZSS(BinaryBigEndian stream, int uncompressedSize)
        {
            this.uncompressedSize = uncompressedSize;
            this.stream = stream;
        }

        bool LastByte() { return stream.BaseStream.Position == stream.BaseStream.Length; }

        private void ClearDict()
        {
            for (var i = 0; i < DICT_SIZE; i++)
                dictionary[i] = 0x20; // ' ' in ascii
            DI = (short)(DICT_SIZE - MAX_MATCH);
        }

        private byte ReadByte()
        {
            NR++;
            return stream.ReadByte();
        }

        private byte[] ReadBytes(int bytes)
        {
            return stream.ReadBytes(bytes);
        }

        // Write to output and dictionary
        void WriteByte(byte b)
        {
            output[OI++] = b;
            dictionary[(DI++ % DICT_SIZE)] = b;
        }

        private void WriteBytes(byte[] bytes)
        {
            foreach (var b in bytes)
            {
                if (OI >= uncompressedSize)
                    return;
                output[OI++] = b;
            }
        }

        private byte ReadDict()
        {
            return dictionary[(DO++ % DICT_SIZE)];
        }

        private Int16 ReadInt16()
        {
            return stream.ReadInt16();
        }

        private void ReadBlock(int N)
        {
            NR = 0; // The amount of bytes we have read in the current block so far
            if (N < 0) // Uncompressed / literal block
            {
                WriteBytes(ReadBytes(N * -1)); // We just read N bytes and write to the output buffer. Dictionary is untouched.
            }
            else // N > 0
            {
                ClearDict();
                // @Flag
                while (true)
                {
                    if (NR >= N || LastByte())
                        return; // Go to @Start

                    // Read flag byte
                    FL = ReadByte();
                    if (NR >= N || LastByte())
                        return; // Go to @Start

                    for (var x = 0; x < 8; x++)
                    {
                        if (FL % 2 == 1) // @FLodd, normal byte
                        {
                            // Read byte from stream and put it in the output buffer and dictionary.
                            WriteByte(ReadByte());
                            if (NR >= N)
                                return;
                        }
                        else // @FLeven, encoded dictionary offset
                        {
                            if (NR >= N)
                                return;

                            // Read dictionary offset byte
                            DO = ReadByte();

                            if (NR >= N)
                                return;

                            // Length byte
                            var LB = ReadByte();

                            DO |= (short)((LB & 0xF0) << 4);    // Prepend the high-nibble (first 4 bits) from LB to DO
                            L = (int)((LB & 0x0F) + MIN_MATCH); // and remove it from LB and add MIN_MATCH
                            for (var i = 0; i < L; i++)
                            {
                                // Read a byte from the dictionary at DO, increment index and write to output and dictionary at DI.
                                WriteByte(ReadDict());
                            }
                        }
                        FL = (byte)(FL >> 1); // @flagNext
                        if (LastByte())
                            return;
                    }
                }
            }
        }

        public byte[] Decompress() {
            output = new byte[uncompressedSize];
            dictionary = new byte[DICT_SIZE];

            while(!LastByte()) // @Start
            {
                N = ReadInt16(); // How many bytes to read in the next block
                if (N == 0) // No bytes, so exit
                    break;
                ReadBlock(N);
            }
            return output;
        }
    }

    class BinaryBigEndian : BinaryReader
    {
        public BinaryBigEndian(System.IO.Stream stream) : base(stream) { }

        public override int ReadInt32()
        {
            var data = base.ReadBytes(4);
            Array.Reverse(data);
            return BitConverter.ToInt32(data, 0);
        }

        public override Int16 ReadInt16()
        {
            var data = base.ReadBytes(2);
            Array.Reverse(data);
            return BitConverter.ToInt16(data, 0);
        }

        public override Int64 ReadInt64()
        {
            var data = base.ReadBytes(8);
            Array.Reverse(data);
            return BitConverter.ToInt64(data, 0);
        }

        public override UInt32 ReadUInt32()
        {
            var data = base.ReadBytes(4);
            Array.Reverse(data);
            return BitConverter.ToUInt32(data, 0);
        }

    }

    public enum ReadError
    {
        Unknown,
        FileDoesntExist,
        NotValidMasterDat,
        Success
    }

    public class FO1File
    {
        public string fullPath;
        public string name;
        public bool packed;
        public int offset;
        public int size;
        public int packedSize;

        public byte[] getData(FileStream stream)
        {
            return packed ? getCompressedBytes(stream) : getBytes(stream);
        }

        public byte[] getBytes(FileStream stream)
        {
            var r = new BinaryBigEndian(stream);
            r.BaseStream.Seek(offset, SeekOrigin.Begin);
            return r.ReadBytes(size);
        }

        public byte[] getCompressedBytes(FileStream stream)
        {
            // Create a new stream so that we are thread safe.
            var s = new MemoryStream();
            BinaryBigEndian r;
            stream.Seek(offset, SeekOrigin.Begin);
            // Copy packedSize amount of bytes from the original dat stream to our new memory stream.
            for (int i = 0; i < packedSize; i++)
                s.WriteByte((byte)stream.ReadByte());

            r = new BinaryBigEndian(s);
            r.BaseStream.Seek(0, SeekOrigin.Begin);

            var LZSS = new FO1LZSS(r, size);
            var bytes = LZSS.Decompress();
            
            s.Dispose();
            r.Dispose();

            return bytes;
        }
    }

    public class FO1Dir
    {
        public string name;
        public int fileCount;
        public List<FO1File> files = new List<FO1File>();
    }

    // https://falloutmods.fandom.com/wiki/DAT_file_format
    public class FO1Dat
    {
        int dirCount; // number of directories
        int unknown; // Usually 0x0A (0x5E for master.dat)
        int unknown2; // Always 0
        int unknown3; // Checksum?
        FileStream fileStream;
        List<FO1Dir> directories;

        public byte[] getData(FO1File file)
        {
            return file.getData(fileStream);
        }

        public FO1File getFile(string path)
        {
            var dir = path.Split('\\').ToList();
            var file = dir.Last();
            dir.Remove(dir.Last());

            var found = directories.Where(x => x.name == string.Join("\\", dir)).SingleOrDefault();
            if (found == null)
                return null;
            return found.files.Where(x => x.name == file).SingleOrDefault();
        }

        private string ReadString(BinaryBigEndian r)
        {
            var len = r.ReadByte();
            return Encoding.ASCII.GetString(r.ReadBytes(len));
        }

        public ReadError Open(string filename)
        {
            if (!File.Exists(filename))
                return ReadError.FileDoesntExist;

            directories = new List<FO1Dir>();
            fileStream = File.OpenRead(filename);
            var r = new BinaryBigEndian(fileStream);
            dirCount = r.ReadInt32();
            unknown = r.ReadInt32();
            unknown2 = r.ReadInt32();
            unknown3 = r.ReadInt32();

            if(unknown != 0x5E || unknown2 != 0)
                return ReadError.NotValidMasterDat;
            for (var i = 0; i < dirCount; i++)
            {
                directories.Add(new FO1Dir() { name = ReadString(r) });
            }

            for (var i=0; i < dirCount;i++)
            {
                var dir = directories[i];
                dir.fileCount = r.ReadInt32();
                r.ReadInt32(); // unknown4
                r.ReadInt32(); // unknown5
                r.ReadInt32(); // unknown6
                for (var y = 0; y < dir.fileCount; y++)
                {
                    var name = ReadString(r);
                    var packed = r.ReadInt32() == 0x40;
                    var offset = r.ReadInt32();
                    var size = r.ReadInt32();
                    var sizePacked = r.ReadInt32();
                    dir.files.Add(new FO1File
                    {
                       packed = packed,
                       name = name,
                       fullPath = dir.name + "\\" + name,
                       offset = offset,
                       size = size,
                       packedSize = sizePacked
                    });
                }
            }

            return ReadError.Success;
        }
    }
}

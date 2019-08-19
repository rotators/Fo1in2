using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace undat_ui
{
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


        private readonly object streamLock = new object();

        public byte[] getData(MemoryStream stream)
        {
            return packed ? getCompressedBytes(stream) : getBytes(stream);
        }

        public byte[] getBytes(MemoryStream stream)
        {
            var r = new BinaryBigEndian(stream);
            r.BaseStream.Seek(offset, SeekOrigin.Begin);
            return r.ReadBytes(size);
        }

        

        // Implemented by following https://falloutmods.fandom.com/wiki/DAT_file_format#Fallout_1_LZSS_uncompression_algorithm
        public byte[] getCompressedBytes(MemoryStream stream)
        {
            // create a new stream so that we are thread safe.
            var s = new MemoryStream();
            BinaryBigEndian r;
            lock (streamLock) {
                stream.Seek(offset, SeekOrigin.Begin);
                for (int i = 0; i < packedSize; i++)
                    s.WriteByte((byte)stream.ReadByte());

                r = new BinaryBigEndian(s);
                r.BaseStream.Seek(0, SeekOrigin.Begin);
            }

            //var correct = File.ReadAllBytes(@"D:\Fallout\fo1_master\"+this.fullPath);

            int uidx = 0;
            
            short DICT_SIZE = 4096;
            short MIN_MATCH = 3;
            short MAX_MATCH = 18;

            //string debug = "";
            byte[] output = new byte[size];
            byte[] dictionary = new byte[DICT_SIZE];

            short N;    // number of bytes to read
            short NR;   // bytes read
            short DO=0; // dictionary offset - for reading
            short DI;   // dictionary index - for writing
            int L;      // match length
            byte FL;    // Flags indicating the compression status of up to 8 next characters.

            void _cleardict()
            {
                for (var i = 0; i < DICT_SIZE; i++)
                    dictionary[i] = 0x20;
                DI = (short)(DICT_SIZE - MAX_MATCH);
            }

            bool _lastbyte() { return r.BaseStream.Position == r.BaseStream.Length; }
            byte _readbyte()
            {
                NR++;
                return r.ReadByte();
            }

            byte _readdict()
            {
                if (DO == 4096)
                    DO = 0;
                var b = dictionary[DO];
                if (DO++ == 4096)
                    DO = 0;
                return b;
            }

            void _writedict(byte b)
            {
                if (DI == 4096)
                    DI = 0;
                dictionary[DI] = b;
                if (DI++ == 4096)
                    DI = 0;
            }

            void _write(byte[] by)
            {
                if (uidx >= size)
                    return;
                else
                {
                    foreach (var b in by)
                    {
                        if (uidx >= size)
                            return;
                        output[uidx] = b;
                        /*if(output[uidx] != correct[uidx])
                        {
                            var uc = output[uidx];
                            var cb = correct[uidx];

                            throw new Exception("Byte diff in uncompressed!");
                        }*/

                        uidx++;
                    }
                }

            }

            void _writeb(byte b)
            {
                if (uidx >= size)
                    return;

                output[uidx] = b;
                /*if (output[uidx] != correct[uidx])
                {
                    var cb = correct[uidx];
                    var ub = output[uidx];
                    throw new Exception($"Byte diff in compressed block!");
                }*/

                uidx++;
            }

            _cleardict();

            var gotoStart = false;

            while (true) // @Start
            {
                //if (uidx >= size)
                //    break;
                if (_lastbyte())
                    break;
                gotoStart = false;
                N = r.ReadInt16(); // How many bytes to read
                NR = 0;
                if(N == 0) // No bytes, so exit
                    break;

                if (N < 0)
                {
                    var b = r.ReadBytes(N * -1);
                   // Array.Reverse(b); // Reverse since it's big endian
                    _write(b);
                }
                else // N > 0
                {
                    _cleardict();
                    // @Flag
                    while (true)
                    {
                        if (gotoStart)
                            break;

                        if (_lastbyte())
                            break;

                        if (NR >= N || _lastbyte())
                            break; // Go to @Start

                        FL = _readbyte();
                        if(NR >= N || _lastbyte())
                            break; // Go to @Start

                        for (var x = 0; x < 8; x++)
                        {
                            if (FL % 2 == 1) // @FLodd
                            {
                                var b = _readbyte();
                                _writeb(b);
                                _writedict(b);
                                if (NR >= N)
                                {
                                    gotoStart = true;
                                    break; // Go to @Start
                                }
                            }
                            else // @FLeven
                            {
                                if (uidx >= size)
                                    break;

                                if (NR >= N)
                                {
                                    gotoStart = true;
                                    break; // Go to @Start
                                }

                               
                                DO = _readbyte();

                                if (NR >= N)
                                {
                                    gotoStart = true;
                                    break; // Go to @Start
                                }

                                var LB = _readbyte();
                                /*if (NR >= N)
                                {
                                    gotoStart = true;
                                    break; // Go to @Start
                                }*/

                                DO |= (short)((LB & 0xF0) << 4); //  (short)((O | (L & 0xF0) << 4)); // Prepend the high-nibble (first 4 bits) from L to DO
                                L = (int)((LB & 0x0F) + MIN_MATCH); // and remove it from L (L = L & 0x0F).
                                for (var i = 0; i < L; i++)
                                {
                                    var b = _readdict();
                                    _writeb(b);
                                    _writedict(b);
                                }
                            }
                            FL = (byte)(FL >> 1); // @flagNext
                            if (_lastbyte())
                            {
                                gotoStart = true;
                                break;
                            }
                        }
                    }
                }
            }
            s.Dispose();
            r.Dispose();

            return output;
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
        MemoryStream memStream;
        List<FO1Dir> directories;

        public byte[] getData(FO1File file)
        {
            return file.getData(memStream);
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

            if(unknown != 94 && unknown2 != 0)
                return ReadError.NotValidMasterDat;

            var ascii = Encoding.ASCII;

            for (var i = 0; i < dirCount; i++)
            {
                var len = r.ReadByte();
                var name = ascii.GetString(r.ReadBytes(len));
                directories.Add(new FO1Dir()
                {
                    name = name
                });
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
                    var len = r.ReadByte();
                    var name = ascii.GetString(r.ReadBytes(len));
                    var packed = r.ReadInt32() == 64;
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

            this.memStream = new MemoryStream();
            this.fileStream.Position = 0;
            this.fileStream.CopyTo(this.memStream);

            return ReadError.Success;
        }
    }
}

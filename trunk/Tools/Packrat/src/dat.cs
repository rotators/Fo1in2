using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Text;

namespace Packrat
{

    public class Adler32Computer
    {
        private int a = 1;
        private int b = 0;
        private static readonly int Modulus = 65521;

        public int Checksum(byte[] data, int offset, int length)
        {
            for (int counter = 0; counter < length; ++counter)
            {
                a = (a + (data[offset + counter])) % Modulus;
                b = (b + a) % Modulus;
            }
            return ((b * 65536) + a);
        }
    }

    public class DatFile
    {
        public string diskPath;
        public string datPath;
        public bool compressed;
        public byte[] bytes;
        public byte[] packedBytes;
        public int size;
        public int packedSize;
        public int offset;

        public static DatFile FromFile(string diskPath, string datPath, bool compress)
        {
            var file = new DatFile();
            var name = Path.GetFileName(diskPath);
            file.diskPath = diskPath;
            file.datPath = datPath + "\\"+name;
            file.compressed = compress;

            using (FileStream originalFileStream = File.OpenRead(diskPath))
            {
                var mem = new MemoryStream();
                originalFileStream.CopyTo(mem);
                file.bytes = mem.ToArray();
                file.size = (int)mem.Length;
                if (compress)
                {
                    MemoryStream output = new MemoryStream();
                    using (DeflateStream dstream = new DeflateStream(output, CompressionLevel.Optimal))
                    {
                        dstream.Write(file.bytes, 0, file.size);
                    }
                    var adler = new Adler32Computer();
                    var arr = new List<byte>(output.ToArray());
                    // Calculate adler checksum and put it at the end in Big-Endian.
                    var check = BitConverter.GetBytes(adler.Checksum(arr.ToArray(), 0, (int)arr.Count)).Reverse().ToArray();
                    arr.AddRange(check);
                    // Add zlib headers
                    // 78 DA - Best Compression 
                    arr.Insert(0, (byte)0xDA);
                    arr.Insert(0, (byte)0x78);

                    file.packedBytes = arr.ToArray();
                    file.packedSize = file.packedBytes.Length;
                }
                else
                {
                    file.packedSize = file.size;
                }
            }

            return file;
        }
    }

    public class Dat
    {
        public static void CreateDat(string datPath, List<DatFile> files)
        {
            if (File.Exists(datPath))
                File.Delete(datPath);
            using (var br = new BinaryWriter(File.Open(datPath, FileMode.CreateNew)))
            {
                foreach (var f in files)
                {
                    f.offset = (int)br.BaseStream.Position;
                    br.Write(f.compressed ? f.packedBytes : f.bytes);
                }
                int count = files.Count();
                br.Write(count);

                int treeOffset = (int)br.BaseStream.Position;
                foreach (var f in files) // DirTree
                {
                    byte comp = (byte)(f.compressed ? 0x1 : 0x0);
                    br.Write((int)f.datPath.Length);
                    br.Write(Encoding.ASCII.GetBytes(f.datPath));
                    br.Write(comp);
                    br.Write(f.size);
                    br.Write(f.packedSize);
                    br.Write(f.offset);
                }
                br.Write((int)(br.BaseStream.Position - treeOffset) + 4); // TreeSize
                br.Write((int)(br.BaseStream.Position + 4)); // DataSize
            }
        }
    }
}

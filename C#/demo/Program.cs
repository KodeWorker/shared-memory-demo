// https://blog.csdn.net/zcz_822/article/details/105858962
// https://stackoverflow.com/questions/10806518/write-string-data-to-memorymappedfile

using System;
using System.IO.MemoryMappedFiles;

namespace demo
{
    class Program
    {
        static void Main(string[] args)
        {
            //memory size
            int size = 1024;

            //create shared memory
            MemoryMappedFile shareMemory = MemoryMappedFile.CreateOrOpen("global_share_memory", size);

            Console.WriteLine("Create shared memory");

            //System.Threading.Thread.Sleep(1000);
            var stream = shareMemory.CreateViewStream(0, size);

            /*
            string value = "Hello World";
            byte[] data = System.Text.Encoding.UTF8.GetBytes(value);
            stream.Write(data, 0, data.Length);
            */

            // Write Shared Memory
            string value = "Hello Watermelon";
            byte[] data = System.Text.Encoding.UTF8.GetBytes(value);
            MemoryMappedViewAccessor accessor = shareMemory.CreateViewAccessor();
            accessor.Write(0, (ushort)data.Length);
            accessor.WriteArray(0, data, 0, data.Length);

            /*
            byte[] result = new byte[stream.Length];
            stream.Read(result, 0, result.Length);
            Console.WriteLine("Data string in shared memory: " + System.Text.Encoding.Default.GetString(result));
            */

            // Read Shared Memory
            ushort Size = accessor.ReadUInt16(0);
            byte[] result = new byte[Size];
            accessor.ReadArray(0, result, 0, result.Length);
            Console.WriteLine("Data string in shared memory: " + System.Text.Encoding.Default.GetString(result));

            stream.Dispose();

            Console.ReadKey();
        }
    }
}

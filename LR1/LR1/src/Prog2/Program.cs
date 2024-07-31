using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Management; // for windows management
using System.Text;
using System.Threading.Tasks;

namespace Prog2
{
    class Program
    {
        static void Main(string[] args)
        {
            BinaryWriter bw;
            string res_string = "";

            // Get serial number of motherboard
            string query = "SELECT * FROM Win32_BaseBoard";
            ManagementObjectSearcher searcher = new ManagementObjectSearcher(query);

            foreach (ManagementObject info in searcher.Get())
                res_string = info.GetPropertyValue("SerialNumber").ToString();
            // Activation of the first program
            try
            {
                //bw = new BinaryWriter(File.Open(@"D:\MPEI\Security\LR1\LR1\src\Prog1\bin\Release\Prog1.exe", FileMode.Open));
                bw = new BinaryWriter(File.Open(@"Prog1.exe", FileMode.Open));
                
            }
            catch (IOException io)
            {
                Console.WriteLine("File open error " + io.Message);
                Console.ReadLine();
                return;
            }

            int seek_start = 0xA52;

            for (int i=0;i< res_string.Length;i++)
            {
                bw.Seek(seek_start, SeekOrigin.Begin);
                seek_start += 2;
                bw.Write(res_string[i]);
            }
            // Close file         
            bw.Close();
            Console.WriteLine("Activation completed successfully!\nHave a good day!");
            Console.ReadLine();
        }
    }
}

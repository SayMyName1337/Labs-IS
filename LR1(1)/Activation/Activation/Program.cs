using System;
using System.Collections.Generic;
using System.Linq;
using System.Management; // for getting SN of motherboard
using System.Text;
using System.Threading.Tasks;
using System.IO; // for open/close files
using System.Runtime.CompilerServices;

namespace Activation
{
    class Program
    {
        public static string getMotherboardSN()
        {
            string serial = "";

            try
            {
                ManagementObjectSearcher mos = new ManagementObjectSearcher("SELECT * FROM Win32_BaseBoard");
                ManagementObjectCollection moc = mos.Get();

                foreach (ManagementObject mo in moc)
                {
                    serial = (string)mo["SerialNumber"];
                }
            }

            catch (Exception ex)
            {
                Console.WriteLine("Error: " + ex.ToString());
            }

            return serial;
        }

        //string path = @"D:\MPEI\Security\LR1\Lab1(WMI)\Lab1(WMI)\bin\Release\lab1(WMI).exe";

        public static void Main(string[] args)
        {
            string path = @"D:\MPEI\Security\LR1\Lab1(WMI)\Lab1(WMI)\bin\Release\lab1(WMI).exe";

            using (FileStream fstream = File.OpenRead(path)) 
            { 
                if (fstream != null)
                 {
                     fstream.Seek (0x9B0, SeekOrigin.Begin);
                     
                 }
            }
        }
    }
}

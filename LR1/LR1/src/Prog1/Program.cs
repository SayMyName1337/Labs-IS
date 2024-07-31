using System;
using System.Collections.Generic;
using System.Linq;
using System.Management; // for windows management
using System.Text;
using System.Threading.Tasks;

namespace Prog1
{
    class Program
    {    
        static string BoardSerial = "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$";
        static void Main(string[] args)
        {            
            string res_string="";

            // Get serial number of motherboard
            string query = "SELECT * FROM Win32_BaseBoard";
            ManagementObjectSearcher searcher = new ManagementObjectSearcher(query);

            foreach (ManagementObject info in searcher.Get())
                res_string =info.GetPropertyValue("SerialNumber").ToString();
            // Truncate the length of the BoardSerial string to the length of the received serial number
            BoardSerial = BoardSerial.Substring(0, res_string.Length);
            // Check the serial number of motherboard
            if (BoardSerial== res_string)
            {
                Console.WriteLine("=========== Hello! ===========");
                Console.WriteLine("====== Access is allowed ======");
                Console.WriteLine("Serial number of motherboard - {0}",res_string);
            } else Console.WriteLine("Attention!\nUnauthorized access\nAccess denied!\nInvalid serial number.");
            Console.ReadLine();
        }
    }
}
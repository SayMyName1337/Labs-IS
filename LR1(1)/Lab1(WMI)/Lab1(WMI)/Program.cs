//using System;
//using System.Collections.Generic;
//using System.Linq;
using System;
using System.Management;
//using System.Text;
//using System.Threading.Tasks;

namespace GetUniqueIDofMotherboard
{
    class Program
    {
        //Get motherboard serial number
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
        
        string IDMotherboard = "####################"; // SN = 18 symbols, add 2 # for stock

        static void Main(string[] args)
        {
                //Write into console the serial number of motherboard
                Console.WriteLine("Motherboard serial number is: " + getMotherboardSN());

                Console.Read();
        }

//        Get motherboard serial number
//        public static string getMotherboardSN()
//        {
//            ManagementObjectSearcher mos = new ManagementObjectSearcher("SELECT * FROM Win32_BaseBoard");
//            ManagementObjectCollection moc = mos.Get();
//            string serial = "";
//
//            foreach (ManagementObject mo in moc)
//            {
//                serial = (string)mo["SerialNumber"];
//            }
//            return serial;  
//        }


     }
}
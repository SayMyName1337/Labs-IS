/* The code of interest is in the subroutine GetDriveGeometry(). The
   code in main shows how to interpret the results of the call. */

#include <windows.h>
#include <winioctl.h>
#include <stdio.h>

BOOL GetDriveGeometry(DISK_GEOMETRY* pdg)
{
    HANDLE hDevice;               // handle to the drive to be examined 
    BOOL bResult;                 // results flag
    DWORD junk;                   // discard results

    hDevice = CreateFile(L"\\\\.\\PhysicalDrive0",  // drive to open
        0,                // no access to the drive
        FILE_SHARE_READ | // share mode
        FILE_SHARE_WRITE,
        NULL,             // default security attributes
        OPEN_EXISTING,    // disposition
        0,                // file attributes
        NULL);            // do not copy file attributes

    if (hDevice == INVALID_HANDLE_VALUE) // cannot open the drive
    {
        wprintf(L"CreateFile() failed!\n");
        return (FALSE);
    }

    bResult = DeviceIoControl(hDevice,  // device to be queried
        IOCTL_DISK_GET_DRIVE_GEOMETRY,  // operation to perform
        
        //IOCTL_SMART_RCV_DRIVE_DATA,
        
        NULL, 0, // no input buffer
        pdg, sizeof(*pdg),     // output buffer
        &junk,                 // # bytes returned
        (LPOVERLAPPED)NULL);  // synchronous I/O

    CloseHandle(hDevice);

    return (bResult);
}

int wmain(int argc, WCHAR* argv[])
{
    DISK_GEOMETRY pdg;            // disk drive geometry structure
    BOOL bResult;                 // generic results flag
    ULONGLONG DiskSize;           // size of the drive, in bytes

    bResult = GetDriveGeometry(&pdg);

    if (bResult)
    {
        //wprintf(L"Cylinders = %I64d\n", pdg.Cylinders);
        //wprintf(L"Tracks/cylinder = %ld\n", (ULONG)pdg.TracksPerCylinder);
        //wprintf(L"Sectors/track = %ld\n", (ULONG)pdg.SectorsPerTrack);
        //wprintf(L"Bytes/sector = %ld\n", (ULONG)pdg.BytesPerSector);

        DiskSize = pdg.Cylinders.QuadPart * (ULONG)pdg.TracksPerCylinder * (ULONG)pdg.SectorsPerTrack * (ULONG)pdg.BytesPerSector;
        wprintf(L"Disk size = %I64d (Bytes) = %I64d (Gb)\n", DiskSize, DiskSize / (1024 * 1024 * 1024));
    }
    else
    {
        wprintf(L"GetDriveGeometry() failed. Error %ld.\n", GetLastError());
    }
    system ("pause");
    return ((int)bResult);
 
}

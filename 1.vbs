On Error Resume Next
Set objService = GetObject("winmgmts:{impersonationLevel=impersonate}!\\.\root\CIMV2")
If Err.Number <> 0 Then
	WScript.Echo Err.Number & ": " & Err.Description
	WScript.Quit
End If
For Each objObject In objService.ExecQuery("SELECT * FROM Win32_BaseBoard")
	WScript.Echo objObject.Caption 'наименование устройства
	WScript.Echo objObject.Description 'описание
	WScript.Echo objObject.Manufacturer 'производитель
	WScript.Echo objObject.Product 'тип, определённый производителем
	WScript.Echo objObject.SerialNumber 'серийный номер производителя
	WScript.Echo objObject.Tag 'идентификатор в системе
	WScript.Echo objObject.Version 'версия
Next
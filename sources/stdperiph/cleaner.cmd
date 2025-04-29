@echo off

:remove
@echo Dang xoa
@echo ========
FOR /F "tokens=*" %%C IN ('DIR "%~dp0\*.bak" /S /B') DO @echo Dang xoa "%%C" & DEL /F "%%C"
FOR /F "tokens=*" %%C IN ('DIR "%~dp0\*.scvd" /S /B') DO @echo Dang xoa "%%C" & DEL /F "%%C"
FOR /F "tokens=*" %%C IN ('DIR "%~dp0\*.uv*" /S /B') DO @echo Dang xoa "%%C" & DEL /F "%%C"
FOR /F "tokens=*" %%C IN ('DIR "%~dp0\CMSIS" /S /B') DO @echo Dang xoa "%%C" & RMDIR /S /Q "%%C"
FOR /F "tokens=*" %%C IN ('DIR "%~dp0\Listings" /S /B') DO @echo Dang xoa "%%C" & RMDIR /S /Q "%%C"
FOR /F "tokens=*" %%C IN ('DIR "%~dp0\Objects" /S /B') DO @echo Dang xoa "%%C" & RMDIR /S /Q "%%C"
FOR /F "tokens=*" %%C IN ('DIR "%~dp0\StdPeriph" /S /B') DO @echo Dang xoa "%%C" & RMDIR /S /Q "%%C"
goto exit

:exit
exit
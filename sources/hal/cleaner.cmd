@echo off

:remove
@echo Dang xoa
@echo ========
FOR /F "tokens=*" %%C IN ('DIR "%~dp0\*.bak" /S /B') DO @echo Dang xoa "%%C" & DEL /F "%%C"
FOR /F "tokens=*" %%C IN ('DIR "%~dp0\*.scvd" /S /B') DO @echo Dang xoa "%%C" & DEL /F "%%C"
FOR /F "tokens=*" %%C IN ('DIR "%~dp0\*.uv*" /S /B') DO @echo Dang xoa "%%C" & DEL /F "%%C"
FOR /F "tokens=*" %%C IN ('DIR "%~dp0\MDK-ARM" /S /B') DO @echo Dang xoa "%%C" & RMDIR /S /Q "%%C"
FOR /F "tokens=*" %%C IN ('DIR "%~dp0\*.mxproject" /S /B') DO @echo Dang xoa "%%C" & DEL /F "%%C"
FOR /F "tokens=*" %%C IN ('DIR "%~dp0\*.ioc" /S /B') DO @echo Dang xoa "%%C" & DEL /F "%%C"
FOR /F "tokens=*" %%C IN ('DIR "%~dp0\*.png" /S /B') DO @echo Dang xoa "%%C" & DEL /F "%%C"
goto exit

:exit
exit
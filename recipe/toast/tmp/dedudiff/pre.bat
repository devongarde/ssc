@ECHO OFF
RMDIR /Q /S ..\toast\tmp\dedudiff
MKDIR ..\toast\tmp\dedudiff
ATTRIB -R ..\toast\shadow\dedudiff\changed.inc
COPY /Y /B ..\toast\shadow\dedudiff\original.inc ..\toast\shadow\dedudiff\changed.inc
XCOPY ..\toast\shadow\dedudiff\*.* ..\toast\tmp\dedudiff /S /I /Q /R /Y /B
DEL /F ..\toast\tmp\dedudiff\*.inc
REM some filesystems have crude timestamps
TIMEOUT /T 3
ATTRIB -R ..\toast\shadow\dedudiff\changed.inc
COPY /Y /B ..\toast\shadow\dedudiff\update.inc ..\toast\shadow\dedudiff\changed.inc
powershell (ls ..\toast\shadow\dedudiff\changed.inc).LastWriteTime = Get-Date

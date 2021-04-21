@ECHO OFF
RMDIR /Q /S ..\toast\tmp\copydiff
MKDIR ..\toast\tmp\copydiff
ATTRIB -R ..\toast\shadow\copydiff\changed.html
ATTRIB -R ..\toast\shadow\copydiff\changed.inc
COPY /Y /B ..\toast\shadow\copydiff\original.html ..\toast\shadow\copydiff\changed.html
COPY /Y /B ..\toast\shadow\copydiff\original.inc ..\toast\shadow\copydiff\changed.inc
XCOPY ..\toast\shadow\copydiff\*.* ..\toast\tmp\copydiff /S /I /Q /R /Y /B
DEL /F ..\toast\tmp\copydiff\*.inc
REM some filesystems have crude timestamps
TIMEOUT /T 3
ATTRIB -R ..\toast\shadow\copydiff\changed.html
ATTRIB -R ..\toast\shadow\copydiff\changed.inc
COPY /Y /B ..\toast\shadow\copydiff\update.html ..\toast\shadow\copydiff\changed.html
COPY /Y /B ..\toast\shadow\copydiff\update.inc ..\toast\shadow\copydiff\changed.inc
powershell (ls ..\toast\shadow\copydiff\changed.html).LastWriteTime = Get-Date
powershell (ls ..\toast\shadow\copydiff\changed.inc).LastWriteTime = Get-Date

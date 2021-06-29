@ECHO OFF
RMDIR /Q /S ..\toast\tmp\update
MKDIR ..\toast\tmp\update
XCOPY ..\toast\shadow\update\*.* ..\toast\tmp\update /S /I /Q /R /Y /B
..\..\ssc.exe -f ../toast/shadow/update/update.conf
TIMEOUT /T 3
COPY /B ..\toast\shadow\update\new.inc+,,..\toast\shadow\update\new.inc
COPY /B ..\toast\shadow\update\changed.html+,,..\toast\shadow\update\changed.html

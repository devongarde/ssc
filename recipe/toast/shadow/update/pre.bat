@ECHO OFF
RMDIR /Q /S ..\toast\tmp\update
MKDIR ..\toast\tmp\update
XCOPY ..\toast\shadow\update\*.* ..\toast\tmp\update /S /I /Q /R /Y /B
COPY /B ..\toast\shadow\update\new.inc ..\toast\tmp\new.inc
COPY /B ..\toast\shadow\update\changed.html ..\toast\tmp\changed.html
TIMEOUT /T 4
ECHO " " >> ..\toast\shadow\update\new.inc
ECHO " " >> ..\toast\shadow\update\changed.html

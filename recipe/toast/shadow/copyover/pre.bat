@ECHO OFF
RMDIR /Q /S ..\toast\tmp\copyover
MKDIR ..\toast\tmp\copyover
XCOPY ..\toast\shadow\copy\*.* ..\toast\tmp\copyover /S /I /Q /R /Y /B

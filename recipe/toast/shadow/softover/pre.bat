RMDIR /Q /S ..\toast\tmp\softover
MKDIR ..\toast\tmp\softover
XCOPY ..\toast\shadow\soft\*.* ..\toast\tmp\softover /S /I /Q /R /Y /B

@ECHO OFF
RMDIR /Q /S ..\toast\tmp\deduover
MKDIR ..\toast\tmp\deduover
XCOPY ..\toast\shadow\deduover\*.* ..\toast\tmp\deduover /S /I /Q /R /Y /B

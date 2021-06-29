@ECHO OFF
RMDIR /Q /S ..\toast\tmp\delete
MKDIR ..\toast\tmp\delete
COPY ..\toast\shadow\delete\delete.spec ..\toast\tmp\delete\delete.me

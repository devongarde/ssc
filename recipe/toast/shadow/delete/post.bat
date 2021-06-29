@ECHO OFF
if exist ..\toast\tmp\delete\delete.me (
  echo "'delete.me' has not been deleted"
  exit 3
)

if exist "help.zip" del help.zip
powershell -command compress-archive -Upd ..\help\* help.zip
if exist "help.htb" del help.htb
move help.zip help.htb
copy help.htb ..\..

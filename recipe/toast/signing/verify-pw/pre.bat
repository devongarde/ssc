@ECHO OFF
CD ..\toast\signing\verify-pw
COPY /B /V /Y ..\sign-pw\*.pem 
COPY /B /V /Y ..\sign-pw\*.pfx
COPY /B /V /Y ..\sign-pw\finger*.txt
COPY /B /V /Y ..\sign-pw\*.sig
openssl dgst -verify publickey-pw.pem -keyform PEM -sha256 -signature test-pw.sig -passin file:password.txt ..\..\..\out\sign-pw.out
CD ..\..\..\tea

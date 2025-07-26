@ECHO OFF
CD ..\toast\signing\verify
COPY /B /V /Y ..\sign\*.pem 
COPY /B /V /Y ..\sign\*.pfx
COPY /B /V /Y ..\sign\finger*.txt
COPY /B /V /Y ..\sign\*.sig
openssl dgst -verify publickey.pem -keyform PEM -sha256 -signature test.sig ..\..\..\out\sign.out
CD ..\..\..\tea

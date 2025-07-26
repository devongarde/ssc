@ECHO OFF
CD ..\toast\signing\sign-pw
DEL /Q *.pem finger*.txt *.pfx *.sig

rem Generate Private Key and Certificate using RSA 256 encryption (4096-bit key)
openssl req -x509 -newkey rsa:4096 -keyout privatekey-pw.pem -out certificate-pw.pem -days 14 -config openssl-pw.cnf -noenc -passout file:password.txt

rem Generate PKCS#12 (P12) file for cert; combines both key and certificate together
openssl pkcs12 -export -inkey privatekey-pw.pem -in certificate-pw.pem -passout file:password.txt -out cert-pw.pfx

rem Generate SHA256 Fingerprint for Certificate and export to a file
openssl x509 -noout -fingerprint -sha256 -inform pem -in certificate-pw.pem -passin file:password.txt >> fingerprint-pw.txt

rem Output public key
openssl x509 -pubkey -noout -in certificate-pw.pem -passin file:password.txt > publickey-pw.pem

CD ..\..\..\tea

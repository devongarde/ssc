cd ../toast/signing/sign
rm -rf *.pem finger*.txt *.pfx *.sig

# Generate Private Key and Certificate using RSA 256 encryption (4096-bit key)
openssl req -x509 -newkey rsa:4096 -keyout ../toast/tmp/sign/privatekey.pem -out ../toast/tmp/sign/certificate.pem -days 14 -config ../toast/other/sign/openssl.cnf -noenc

# Generate PKCS#12 (P12) file for cert; combines both key and certificate together
openssl pkcs12 -export -inkey ../toast/tmp/sign/privatekey.pem -in ../toast/tmp/sign/certificate.pem -out ../toast/tmp/sign/cert.pfx

# Generate SHA256 Fingerprint for Certificate and export to a file
openssl x509 -noout -fingerprint -sha256 -inform pem -in ../toast/tmp/sign/certificate-pw.pem -passin file:../toast/other/sign/password.txt >> ../toast/tmp/sign/fingerprint-pw.txt

# Output public key
openssl x509 -pubkey -noout -in ../toast/tmp/sign/certificate.pem > ../toast/tmp/sign/publickey.pem

cd ../../../tea

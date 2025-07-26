cd ../toast/signing/verify
cp -f ../sign/*.pem .
cp -f ../sign/*.pfx .
cp -f ../sign/finger*.txt .
cp -f ../sign/*.sig .
openssl dgst -verify publickey.pem -keyform PEM -sha256 -signature test.sig ../../../out/sign.out
cd ../../../tea

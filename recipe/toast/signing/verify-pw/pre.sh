cd ../toast/signing/verify-pw
cp -f ../sign-pw/*.pem .
cp -f ../sign-pw/*.pfx .
cp -f ../sign-pw/finger*.txt .
cp -f ../sign-pw/*.sig .
openssl dgst -verify publickey-pw.pem -keyform PEM -sha256 -signature test-pw.sig ../../../out/sign-pw.out
cd ../../../tea

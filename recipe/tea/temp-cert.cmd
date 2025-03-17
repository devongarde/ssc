rem you will need to change these parameters to match your system
powershell -Command "New-SelfSignedCertificate -Type Custom -Subject 'CN=Test Signer, OU=Test O=SSC, C=LU' -KeyUsage DigitalSignature -FriendlyName 'SSC Temp Test Certificate' -CertStoreLocation 'Cert:\CurrentUser\My' -TextExtension @('2.5.29.37={text}1.3.6.1.5.5.7.3.3', '2.5.29.19={text}')"

rem Note these:

rem Get-ChildItem | Format-Table Subject, FriendlyName, Thumbprint
rem Remove-Item -Path cert:\CurrentUser\My\THUMBPRINT -DeleteKey
rem (thanks to https://www.pkisolutions.com/deleting-certificates-from-windows-certificate-store-programmatically-powershell-and-c/)

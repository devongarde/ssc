rm -rf ../toast/tmp/copydiff
mkdir -p ../toast/tmp/copydiff
chmod 644 ../toast/shadow/copydiff/changed.html ../toast/shadow/copydiff/changed.inc
cp -f  ./toast/shadow/copydiff/original.html ../toast/shadow/copydiff/changed.html
cp -f  ./toast/shadow/copydiff/original.inc ../toast/shadow/copydiff/changed.inc
cp -Rfp ../toast/shadow/copydiff/*.* ../toast/tmp/copydiff
# some filesystems have crude timestamps
sleep 3
chmod 644 ../toast/shadow/copydiff/changed.html ../toast/shadow/copydiff/changed.inc
cp -f  ./toast/shadow/copydiff/update.html ../toast/shadow/copydiff/changed.html
cp -f  ./toast/shadow/copydiff/update.inc ../toast/shadow/copydiff/changed.inc

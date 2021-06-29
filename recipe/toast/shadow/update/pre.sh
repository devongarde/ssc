rm -rf ../toast/tmp/update
mkdir -p ../toast/tmp/update
cp -Rfp ../toast/shadow/update/*.* ../toast/tmp/update
./ssc -f ../toast/shadow/update/update.conf
touch ../toast/shadow/update/new.inc
touch ../toast/shadow/update/changed.html

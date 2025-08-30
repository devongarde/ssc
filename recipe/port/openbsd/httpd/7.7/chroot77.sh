#!/bin/sh
#
# intended for OpenBSD 7.7
#
# ensure the dependencies mentioned in dependencies.sh are installed
#
# put a copy of the ssc you build into bin (as created below)
#

cd /var/www
mkdir -p bin usr/lib usr/libexec usr/local/lib

cp /bin/sh bin
cp /bin/echo bin
cp /usr/bin/logger bin

cp /usr/lib/libc++.so.* usr/lib
cp /usr/lib/libc++abi.so.* usr/lib
cp /usr/lib/libc.so.* usr/lib
cp /usr/lib/libcurses.so.* usr/lib
cp /usr/lib/libm.so.* usr/lib
cp /usr/lib/libpthread.so.* usr/lib

cp /usr/libexec/ld.so usr/libexec

cp /usr/local/lib/libhunspell-1.7.so.* usr/local/lib
cp /usr/local/lib/libiconv.so.* usr/local/lib
cp /usr/local/lib/libicudata.so.* usr/local/lib
cp /usr/local/lib/libicui18n.so.* usr/local/lib
cp /usr/local/lib/libicuio.so.* usr/local/lib
cp /usr/local/lib/libicutest.so.* usr/local/lib
cp /usr/local/lib/libicutu.so.* usr/local/lib
cp /usr/local/lib/libicuuc.so.* usr/local/lib


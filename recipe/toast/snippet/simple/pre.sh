#!/bin.sh
export SERVER_SOFTWARE=OpenBSD httpd
export SERVER_NAME=example.com
export GATEWAY_INTERFACE=CGI/1.1
export SERVER_PROTOCOL=HTTP/1.1
export SERVER_PORT=80
export REQUEST_METHOD=GET
export HTTP_ACCEPT="text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8"
export SCRIPT_NAME=/cgi-bin/test-cgi
export QUERY_STRING="html.snippet=%3C%21DOCTYPE+HTML%3E%3Chtml%3E%3Chead%3E%3C%2Fhead%3E%0D%0A%3Cbody%3E%3Ch1%3Etest%3C%2Fh1%3E%3C%2Fbody%3E%3C%2Fhtml%3E&html.version=2021%2F04%2F01&general.verbose=4"
export REMOTE_ADDR=192.168.1.1

To get a demo of SSC running in an OpenBSD's httpd server's CGI environment, chrooted, you will need to do at least :

- note the structure of the server's home directory at /var/www;
- enable the OpenBSD daemons httpd and slowcgi;
- build a copy of ssc and place it in /var/www/usr/bin;
- use ldd to note the libraries required by your build of ssc;
- copy those libraries into the corresponding /var/www/usr folders;
- copy any libraries those libraries need too;
- copy the file dance into /var/www/cgi-bin;
- copy the file test.html into /var/www/htdocs;
- ensure all permissions are cromulent;

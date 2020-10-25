ssc
Static Site Checker

an opinionated HTML nitpicker
for hand-made websites

see LICENCE.txt for copyright & licence notice




WARNING: this code is:
- incomplete
- pre-alpha
- IT WILL NOT DO WHAT YOU EXPECT :-)
- do NOT feed it untrusted data





ssc analyses static HTML sites at source:
- HTML 1.0/+/2.0/3.0/3.2/4.00/4.01/5.0/5.1/5.2/5.3/WhatWG July 2020
- SVG 1.0/1.1
- MathML 1
- XHTML 1.0/1.1/2.0, -ish
- broken links (requires curl)
- server side includes
- schema.org microdata 2.x/3.x/4.0/5.0/6.0/7.x/8.0/9.0/10.0
- microformats v1 & v2, as per microformats.org

with opinions on:
- standard english where dialect is required
- perfectly legal but rather messy HTML
- abhorrent HTML such as autoplay on video

It does NOT:
- analyse or even understand scripting languages
- analyse or even understand style languages, except that it picks up class names from CSS
- analyse or even understand XML or any derivative beyond that noted above
- behave in an even vaguely secure manner: its parser is holier than robin's cow
- do what you want or expect




ssc -h
for a usage summary.

ssc -f config_file
analyse site using prepared configuration

ssc directory
analyse website based in directory




To build & run:
1. Build and install boost 1.72
2. Under Windows, open ssc.sln in Visual Studio 2019 & build 64 bit
3. Under Centos 8 / Macos Catalina / Macos HighSierra, build using appropriate makefile
4. install curl (curl.haxx.se) if need be




written by dylan harris
https://dylanharris.org/

dylan harris
swlc AT dylanharris.org
October 2020

Static Site Checker
(an opinionated HTML nitpicker)
version 0.0.75
https://ssc.lu/



(c) 2020 dylan harris
see LICENCE.txt for copyright & licence notice



WARNING: this code is:
- incomplete
- pre-alpha
- IT WILL NOT DO WHAT YOU EXPECT :-)
- do NOT feed it untrusted data



ssc analyses static HTML sites at source:
- HTML 1.0/+/2.0/3.0/3.2/4.00/4.01/5.0/5.1/5.2/5.3/WhatWG July 2020
- SVG 1.0/1.1
- MathML 1/2/3
- XHTML 1.0/1.1/2.0, -ish
- finds broken links (requires curl)
- server side includes, mostly
- schema.org microdata 2.x/3.x/4.0/5.0/6.0/7.x/8.0/9.0/10.0/11.0
- microformats v1 & v2

with opinions on:
- standard english where dialect is required
- perfectly legal but rather untidy HTML
- abhorrent HTML such as autoplay on video

It does NOT:
- do what you want or expect
- behave securely: its parser is holier than robin's cow
- analyse or understand scripts
- analyse or understand styles, beyond nicking class names from CSS
- analyse or understand XML or derivatives except as noted above

It can output 'repaired' HTML (not XHTML) with Server Side Includes merged in place.



ssc -h
for a usage summary.

ssc -f config_file
analyse site using preprepared configuration

ssc directory
analyse website based in directory



To build & run:
1. Set the environment variable SSCPATH to point to the ssc root directory (the one containing recipe)
2. If need be download, build and install boost 1.71 or better (perhaps from boost.org)
3. Set the environment variable BOOST to point to the BOOST home directory
4. -EITHER- build with CMake 3.11 or better ("cd recipe/tea" "cmake ." "make" "ctest" "make install")
5. -OR- build with recipe\tea\ssc201?.sln in Visual Studios 2015/2017/2019 under Windows
6. If need be download, build and install curl (perhaps from curl.haxx.se)
7. Gleefully run ssc



Notes on folder word play:
- recipe: a nod to Vernor Vinge's "A Fire Upon the Deep"
- tea: without tea, nothing works / builders' tea
- sauce: identifies people who presume / obvious
- toast: toasts code / i like burnt toast
- heater: i'm not stopping now



SEE ALSO
build.txt        notes on building ssc
usage.txt        how to use ssc
releasenotes.txt release notes for the current version of ssc
LICENCE.txt      ssc licence information
LICENSE.txt      formal GPL 3 licence



NOTE: the full project includes public specifications hoovered from various websites. I include them
as reference, to facilitate conversation, and to enable precise bug reports.



written by dylan harris
mail@ssc.lu
November 2020

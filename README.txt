Static Site Checker
(an opinionated HTML nitpicker)
version 0.0.104
https://ssc.lu/



(c) 2020,2021 dylan harris
see LICENCE.txt for copyright & licence notice
see W3-LICENCE.txt for additional copyright & licence information



WARNING: this code is:
- incomplete
- pre-alpha
- IT PROBABLY WON'T BEHAVE AS YOU EXPECT :-)
- do NOT feed it untrusted data



ssc analyses static HTML snippets, files and sites:
- HTML 1.0/+/2.0/3.0/3.2/4.00/4.01/5.0/5.1/5.2/5.3 (draft)
- HTML living standard, Jan 2005 to Apr 2021
- SVG 1.0/1.1
- MathML 1/2/3/4 (draft)
- XHTML 1.0/1.1/2.0/5.x
- finds broken links (requires curl)
- server side includes, mostly
- schema.org microdata 2.x/3.x/4.0/5.0/6.0/7.x/8.0/9.0/10.0/11.0/12.0
- microformats v1 & v2

with opinions on:
- standard english where dialect is required
- perfectly legal but sloppy HTML
- abhorrent rudeness such as autoplay on video

It does NOT:
- behave securely: its parser is holier than robin's cow
- analyse or understand scripts
- analyse or understand styles, beyond nicking class names from CSS
- analyse or understand XML or derivatives except as noted above

It can output:
- 'repaired' HTML (not XHTML)
- HTML with resolved Server Side Includes
- JASON summaries of microformat and microdata content
- website statistical information
- updated website with datafile deduplication


ssc -h
for a usage summary.

ssc -f config_file
analyse site using preprepared configuration

ssc directory
analyse website based in directory



To build & run:
1. Set the environment variable SSCPATH to point to the ssc root directory (the one containing recipe)
2. If need be download, build and install ICU 63_1 or better (perhaps from icu-project.org)
3. Set the environment variable ICUPATH to point to the ICU home directory
4. If need be download, build and install boost 1.67 or better (perhaps from boost.org)
5. Set the environment variable BOOST to point to the BOOST home directory
6. -EITHER- build with CMake 3.11 or better ("cd recipe/tea" "cmake ." "make" "ctest" "make install")
7. -OR- build with recipe\tea\ssc201?.sln in Visual Studios 2015/2017/2019 under Windows
8. If need be download, build and install curl (perhaps from curl.haxx.se)
9. Gleefully run ssc



NOTE
SSC can be run in a CGI environment. This is intended for use with OpenBSD's native httpd web server
(https://man.openbsd.org/httpd.8). You are reminded that SSC is pre-alpha software. Do NOT expose it
to untrusted data sources, such as the open web, without taking serious precautions. SSC probably has
more bugs than the Creator's Ultimate All-Beetle Extravaganza (J.B.S. Haldane, apocryphal : "[the
Creator has] an inordinate fondness for beetles.").



Notes on folder names:
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
more licences    licences for content copied from elsewhere



written by dylan harris
mail@ssc.lu
May 2021

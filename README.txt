Static Site Checker
(an opinionated HTML nitpicker)
version 0.1.14
(c) 2020-2023 dylan harris
see LICENCE.txt and LICENSE.txt for copyright & licence notice
https://ssc.lu/
https://github.com/devongarde/ssc



ssc analyses static X/HTML snippets, files and sites:
- HTML 1.0/+/2.0/3.0/3.2/4.00/4.01/5.0/5.1/5.2/5.3-draft
- HTML living standard, Jan 2005 to Jan 2023
- CSS 1/2.0/2.1/2.2 draft Feb 2022
- SVG 1.0/1.1/1.2 Tiny/1.2 Full/2.0/2.x draft Apr 2021
- MathML 1/2/3/4 draft Jul 2022
- XHTML 1.0/1.1/2.0/5.x
- CSS 1
- finds broken links
- server side includes, mostly
- many microdata & RDFa ontologies

with opinions on:
- standard english where dialect is required
- perfectly legal but sloppy HTML
- abhorrent rudeness such as autoplay on videos

It does NOT:
- analyse or understand scripts
- analyse or understand XML or derivatives, except as noted above

It can output:
- 'repaired' HTML (not XHTML)
- HTML with resolved server side includes
- JSONs of ontological content
- website statistical information
- deduplicated websites



ssc -h
for a usage summary.

ssc -f config_file
analyse site using preprepared configuration

ssc directory
analyse website based in directory



To build & run:
1. Follow the build instructions in build.txt
2. Gleefully run ssc. It will misbehave if you are insufficiently
   gleeful.



This is an alpha version of ssc. Despite heavy testing, it may contain
unexpected features. If you encounter such an bug, please help improve
ssc by collecting the following information (where relevant):
- version of ssc;
- precise version of the operating system;
- hardware architecture and system information;
- detailed description of the error and how to cause it;
- copy of output file showing the error;
- copy of pages/website being analysed;
- precise command used;
- configuration file(s) used, if any;
- any ndx file or other pre-existing file used during the run;
- any known workarounds or solutions;
- a dance interpretation of the 'feature';
and emailing everything to mail@ssc.lu (if the collected files are more
than small, please use a public fileserver and email the link). Do NOT
send anything confidential. Furthermore, unless you request otherwise,
we reserve the right to publish some or all of the information sent in
future versions of ssc, usually in the test suite. If you have a fix,
you are invited to submit a pull request on github. Thank you.
Github address: https://github.com/devongarde/ssc



SSC can be run in a CGI environment. This is intended for use with
OpenBSD's native httpd web server (https://man.openbsd.org/httpd.8).
You are reminded that SSC is pre-production software. Do NOT expose it
to untrusted data sources, such as the open web.



Notes on names:
- recipe: a nod to Vernor Vinge's "A Fire Upon the Deep";
- tea: without tea, nothing works; then there's builders' tea;
- sauce: identifies those who presume; and anyway, it's obvious;
- toast: toasts code; i like burnt toast;
- heater: i'm not stopping now;
- unii: my preferred plural of unix: to my ears, both unixes and unices
        sound like they sing castrato.
- andor: and/or sans obsolescence



SEE ALSO
build.txt        notes on building ssc
gen.txt          a model man page
usage.txt        how to use ssc
releasenotes.txt a slight history of releases
LICENCE.txt      ssc licence information
LICENSE.txt      formal GPL 3 licence
more licences    licences for borrowed external content



Background
I have a website, arts & ego, at https://dylanharris.org/. It has
approaching 60G of original content. It contains hand coded HTMLs 2,
3, 4 & 5. It is a complete mess. Despite a long search, I could not
find any tools to properly diagnose its flaws. Anything I did find
was at most cursory.

Then came the cow flu*.

* corvid means crow, thus covid means cow**.

** by the rules of sympathetic spelling.



REMINDER
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.



dylan harris
mail@ssc.lu
December 2022

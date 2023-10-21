Static Site Checker
(an opinionated HTML nitpicker)
version 0.1.42
(c) 2020-2023 dylan harris
see LICENCE.txt and LICENSE.txt for copyright & licence notice
https://ssc.lu/
https://github.com/devongarde/ssc



ssc analyses static X/HTML snippets, files and sites:
- HTML living standard, Jan 2005 to Oct 2023
- HTML Tags/1.0/+/2.0/3.0/3.2/4.00/4.01/5.0/5.1/5.2/5.3-draft
- CSS 1/2.0/2.1/2.2-draft, 2007-2023 snapshots, etc.
- SVG 1.0/1.1/1.2 Tiny/1.2 Full/2.0/2.x-draft
- MathML 1/2/3/4-draft
- XHTML 1.0/1.1/2.0/5.x
- finds broken links
- server side includes, mostly
- many ontologies

with opinions on:
- standard english where dialect is required
- perfectly legal but sloppy HTML
- abhorrent rudeness such as AUTOPLAY on <VIDEO>

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



This is an alpha version of ssc. It is incomplete. What is complete
needs refining. The developer needs coffee.

It may contain unexpected features. If you encounter one, please help
improve ssc by collecting the following information (where relevant)
and forwarding it to the developer:
- version of ssc;
- precise version of the operating system;
- hardware architecture and system information;
- detailed description of the problem;
- detailed description of the steps to recreate it;
- copy of output file/s and relevant logs;
- copy of pages/website being analysed;
- precise command used;
- configuration file/s used, if any;
- any ndx file or other pre-existing file used during the run;
- any known workarounds, fixes or solutions;
- a dance interpretation.
Email everything to mail@ssc.lu (if the collected files are more than
small, please use a public fileserver and email the link). Do NOT send
anything confidential. Furthermore, unless you state otherwise, we
reserve the right to publish some or all of the information sent in
future versions of ssc, usually in the test suite. If you have a fix,
you are invited to submit a pull request on github, at
https://github.com/devongarde/ssc . Thank you.



SSC can be run in a CGI environment. This is intended for use with
OpenBSD's native httpd web server (https://man.openbsd.org/httpd.8).
You are reminded that SSC is not production software. Do NOT expose it
to untrusted data sources, such as those found on the open web.



Notes on names:
- recipe: a nod to Vernor Vinge's "A Fire Upon the Deep";
- tea: without tea, nothing works; then there's builders' tea;
- sauce: makes the dull tasty; identifies linguistically weak pedants;
- toast: toasts code; i liked burnt toast;
- heater: i'm not stopping now;
- unii: my preferred plural of unix: to my ears, both unixes and unices
        sound like they sing castrato.
- andor: and/or sans ancienne; land of Gift (aber nicht das Gift)



SEE ALSO
build.txt        notes on building ssc
gen.txt          a model man page
usage.txt        how to use ssc
releasenotes.txt fishless chips
LICENCE.txt      ssc licence information
LICENSE.txt      formal GPL 3 licence
more licences    licences for borrowed external content



Background
I have a website, arts & ego, at https://dylanharris.org/. It has
approaching 60G of original content. It contains hand coded HTMLs 2
to 5. It is a complete mess. Despite a long search, I could not find
any tools to properly identify its flaws. Anything I did find was at
most cursory.

Then came the cow flu*.
* corvid means crow, thus covid means cow**.
** by the law of sympathetic spelling.



Unabashed Opportunism
If you appreciate modernist poetry or abstract photography, click on
books at https://dylanharris.org/ for gen.



REMINDER
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.



dylan harris
mail@ssc.lu
October 2023

Static Site Checker
(an opinionated HTML nitpicker)
version 0.2.25
(c) 2020-2026 dylan harris
see LICENCE.txt and LICENSE.txt for copyright & licence notices
https://dylanharris.org/ssc/
https://github.com/devongarde/ssc



ssc analyses static websites at source:
- HTML living standard, Jan 2005 to Jan 2026
- HTML Tags/1.0/+/2.0/3.0/3.2/4.00/4.01/5.0/5.1/5.2/5.3-draft
- CSS 1/2.0/2.1/2.2-draft, 2007-2025 snapshots, more
- SVG 1.0/1.1/1.2 Tiny/1.2 Full/2.0/2.x-draft
- MathML 1/2/3/core/4-draft
- XHTML 1.0/1.1/2.0/5.x themselves
- ads.txt, robots.txt, security.txt, WebVTT
- most of ATOM, JSON-LD, RSL, RSS, themselves
- finds broken links
- server side includes, mostly
- many ontologies

with opinions on:
- contradictory flavours/flavors of english
- legal but inefficient HTML
- abhorrent rudeness such as AUTOPLAY on <VIDEO>

It does NOT:
- analyse or understand scripts
- except as noted above, analyse or understand XML or derivatives

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
- a video of a dance interpretation of the issue (might just be
  optional, this).
Email everything to ssc@dylanharris.org (if the collected files are more than
small, please use a public file server and email the link). Do NOT send
anything confidential. Furthermore, unless you state otherwise, we
reserve the right to publish some or all of the information sent in
future versions of ssc, usually in the test suite. If you have a fix,
you are invited to submit a pull request on github at
https://github.com/devongarde/ssc. Thank you.



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



Security
Regarding the EU's Cyber Resilience Act, any security issues should be
reported to ssc@dylanharris.org, and cc'ed to mail@dylanharris.org. For a list
of components used by SSC, please consult the source code.



SEE ALSO
build.txt        notes on building ssc
gen.txt          a model man page
usage.txt        how to use ssc
releasenotes.txt fishless chips
LICENCE.txt      ssc licence information
LICENSE.txt      formal GPL 3 licence
more licences    licences for borrowed external content
SECURITY.md		 security reporting



Background
I have a website, arts & ego, at https://dylanharris.org/. It has
approaching 60G of original content. It contains hand coded HTMLs 2
to 5. It is a complete mess. Despite a long search, I could not find
any tools to properly identify its flaws. Anything I did find was at
most cursory.

Then came the cow flu*.

Hence ssc is a covid project that grew out of hand.

* corvid means crow, thus covid means cow**.
** by the laws of sympathetic spelling.



Unabashed Opportunism
If you appreciate modernist poetry or abstract photography, click on
books at https://dylanharris.org/ for gen.



REMINDER
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.



dylan harris
ssc@dylanharris.org
mail@dylanharris.org
December 2025

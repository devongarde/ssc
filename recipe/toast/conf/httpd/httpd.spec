-Y 1 -f ../toast/conf/httpd/httpd.conf

PASS ../httpd/plumbing/ignorance.css
0 html

PASS ../httpd/index.shtml
195 url_not_found
197 url_not_found
199 url_not_found
201 url_not_found

PASS ../httpd/release-notes.shtml
233 url_not_found
234 url_not_found
235 url_not_found
236 url_not_found
294 url_not_found

PASS ../httpd/help/welcome.html
64 unrecognised_value invalid_attribute_version wrong_version naughty_alt

shadow
0 shadow

LYNX
0 58
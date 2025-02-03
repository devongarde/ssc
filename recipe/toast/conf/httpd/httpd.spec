-Y 1 -f ../toast/conf/httpd/httpd.conf

PASS ../httpd/plumbing/ignorance.css
0 html

PASS ../httpd/index.shtml
250 url_not_found
253 url_not_found

PASS ../httpd/release-notes.shtml
187 url_not_found
188 url_not_found
216 url_not_found

PASS ../httpd/help/welcome.html
39 unrecognised_value invalid_attribute_version wrong_version naughty_alt

shadow
0 shadow

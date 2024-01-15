-Y 1 -f ../toast/type/sgml/sgml.conf

PASS ../toast/type/sgml/index.html
2 naughty_lang

PASS ../toast/type/sgml/bad.html
0 html_unknown_sgml

PASS ../toast/type/sgml/dubious.html
2 attribute_unrecognised unrecognised_attribute

PASS ../toast/type/sgml/dubious2.html
1 html_unrecognised
2 naughty_lang

PASS ../toast/type/sgml/good.html
10 url_not_found

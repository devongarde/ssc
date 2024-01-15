-Y 1 -f ../toast/HTML/1.0/html1.conf

PASS ../toast/HTML/1.0/index.html
1 presume_html_1

PASS ../toast/HTML/1.0/html1-bad.html
0 title_required
1 presume_html_1 unknown_element unknown_element
2 inserted_missing_parent missing_close inserted_missing_parent attribute_unrecognised unrecognised_attribute
4 only_once
5 deprecated_element
7 inserted_missing_closure inserted_missing_closure url_not_found missing_open
11 unknown_element unknown_element
12 empty_character_code
13 urn_undefined
14 unrecognised_value unknown_rel rel_requires_href
15 unrecognised_value unknown_rel rel_requires_href
17 url_not_found url_not_found

PASS ../toast/HTML/1.0/html1-bad2.html
1 inserted_missing_parent missing_close inserted_missing_parent presume_html_1 inserted_missing_closure inserted_missing_closure missing_open
3 deprecated_element
7 unknown_element unknown_element
8 empty_character_code
9 methods_undefined
11 inserted_missing_closure missing_open
22 unrecognised_value unknown_rel
23 rel_requires_href

PASS ../toast/HTML/1.0/html1-good.html
1 presume_html_1

PASS ../toast/HTML/1.0/html1-simple.html
1 presume_html_1

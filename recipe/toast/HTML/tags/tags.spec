-Y 1 -f ../toast/HTML/tags/tags.conf

PASS ../toast/HTML/tags/index.html
1 presume_html_tags

PASS ../toast/HTML/tags/tags-bad.html
0 title_required
1 presume_html_tags unknown_element unknown_element
2 invalid_attribute_version wrong_version base_undefined
5 code_unrecognised_here invalid_character_code
6 unknown_element unknown_element
7 empty_character_code unknown_element missing_close
8 mime
9 chocolate_teapot
13 only_elements
18 inserted_missing_closure
19 missing_open

PASS ../toast/HTML/tags/tags-bad2.html
1 presume_html_tags inserted_missing_closure missing_open
2 only_once
4 deprecated_element
10 only_elements
11 only_elements
12 only_elements

PASS ../toast/HTML/tags/tags-example.html
1 presume_html_tags
2 deprecated_element
4 url_not_found
12 attempted_escape url_not_found

PASS ../toast/HTML/tags/tags-oddities.html
1 presume_html_tags
6 closure_not_xmp missing_open
21 code_unrecognised_here invalid_character_code

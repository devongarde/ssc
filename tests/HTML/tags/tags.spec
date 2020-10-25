-f tests/HTML/tags/tags.conf

PASS tests/HTML/tags/index.html
1 presume_html_tags

PASS tests/HTML/tags/tags-bad.html
0 title_required
1 presume_html_tags ignoring_unknown ignoring_unknown
2 invalid_attribute_version wrong_version base_undefined
5 code_unrecognised_here invalid_character_code
6 invalid_element_version
7 empty_character_code invalid_element_version
9 chocolate_teapot
13 only_elements
18 inserted_missing_closure
19 missing_open

PASS tests/HTML/tags/tags-bad2.html
1 presume_html_tags inserted_missing_closure missing_open
2 only_once
4 deprecated_element
10 only_elements
11 only_elements
12 only_elements

PASS tests/HTML/tags/tags-example.html
1 presume_html_tags
2 deprecated_element

PASS tests/HTML/tags/tags-oddities.html
1 presume_html_tags
6 closure_not_xmp missing_open
21 code_unrecognised_here invalid_character_code

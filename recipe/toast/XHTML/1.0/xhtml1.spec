-f ../toast/XHTML/1.0/xhtml1.conf

PASS ../toast/XHTML/1.0/index.xhtml
1 xhtml_1_0

PASS ../toast/XHTML/1.0/minimal.xhtml
1 xhtml_1_0
3 xhtml_superseded
4 xhtml_superseded

PASS ../toast/XHTML/1.0/x1-good.xhtml
1 xhtml_1_0
10 attribute_required

PASS ../toast/XHTML/1.0/x1-bad.xhtml
1 xhtml_1_0
6 xhtml_element_lc
8 xhtml_element_lc
9 bad_noscript
12 xhtml_quote_values xhtml_attribute_lc xhtml_quote_values missing_close xhtml_enum_lc
13 xhtml_missing_slash
15 xhtml_hex_lc deprecated_attribute
16 xhtml_missing_slash xhtml_existential_makework attribute_required
18 inserted_missing_closure

PASS ../toast/XHTML/1.0/parsing.xhtml
1 xhtml_1_0
22 attribute_required
26 attribute_required

PASS ../toast/XHTML/1.0/mathml-1.xhtml
1 xhtml_1_0

PASS ../toast/XHTML/1.0/math-example.xhtml
1 xhtml_1_0
2 xmlns_namespace
7 reputation
12 attribute_barred

PASS ../toast/XHTML/1.0/svg1-example.xhtml
1 xhtml_1_0
80 attribute_required
91 id_exists
119 url_not_found
238 id_exists
254 missing_close unrecognised_value
256 inserted_missing_closure
266 id_exists
305 newline_in_string newline_in_string
314 id_exists
322 newline_in_string newline_in_string
332 id_exists
428 url_not_found
437 url_not_found
455 attribute_barred
471 unrecognised_value bad_colour
476 id_exists
480 attribute_barred id_exists
511 attribute_required
552 xmlns_namespace unrecognised_value invalid_attribute_version wrong_version

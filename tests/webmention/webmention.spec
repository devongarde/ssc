-f tests/type/type.conf

PASS tests/type/index.html
1 html_5_4
2 naughty_lang

PASS tests/type/metaname-bad.html
1 html_5_4
2 naughty_lang
5 unrecognised_value unrecognised_value
6 unrecognised_value unrecognised_value unrecognised_value unrecognised_value
14 not_img not_img
16 bad_srcset saucy_source

PASS tests/type/metaname-dubious.html
1 html_5_4
2 naughty_lang
5 unrecognised_value unrecognised_value
6 wrong_version unrecognised_value
14 not_img
15 bad_srcset saucy_source

PASS tests/type/metaname-good.html
1 html_5_4
2 naughty_lang

PASS tests/type/metaname-old.html
1 html_3_2
5 wrong_version unrecognised_value
6 dinosaur

PASS tests/type/mimetype-bad.html
1 html_5_4
2 naughty_lang
12 not_img not_img
13 mime
15 mime

PASS tests/type/mimetype-dubious.html
1 html_5_4
2 naughty_lang
12 not_img not_img
13 mime
15 bad_srcset saucy_source
16 mime

PASS tests/type/mimetype-good.html
1 html_5_4
2 naughty_lang
12 bad_srcset saucy_source
13 bad_srcset saucy_source

PASS tests/type/url-bad.html
1 html_5_4
2 naughty_lang
12 url_id_unfound
15 unknown_protocol
16 bad_char
17 bad_char
18 invalid_protocol
19 invalid_ipv4
20 attribute_unrecognised invalid_ipv4 unrecognised_attribute
21 invalid_ipv4
22 invalid_ipv6
23 empty_ipv6
24 malformed_ipv6
25 invalid_ipv6
26 invalid_protocol
27 bad_port
30 url_missing_username
31 url_empty_password url_missing_username
32 empty_host
33 url_empty_password
34 url_empty_password empty_host
35 url_insecure_password
42 not_img
43 url_not_found

PASS tests/type/url-dubious.html
1 html_5_4
2 naughty_lang
11 unknown_protocol
12 url_insecure_password

PASS tests/type/url-good.html
1 html_5_4
2 naughty_lang

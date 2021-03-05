-f ../toast/type/url/url.conf

PASS ../toast/type/url/index.html
2 naughty_lang

PASS ../toast/type/url/bad.html
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
41 bang_path

PASS ../toast/type/url/dubious.html
2 naughty_lang
11 unknown_protocol
12 url_insecure_password

PASS ../toast/type/url/good.html
2 naughty_lang

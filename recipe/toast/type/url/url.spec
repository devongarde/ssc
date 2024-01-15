-Y 1 -f ../toast/type/url/url.conf

PASS ../toast/type/url/index.html
2 naughty_lang

PASS ../toast/type/url/bad.html
2 naughty_lang
12 url_id_unfound
13 character_code
15 unknown_protocol chocolate_teapot
16 chocolate_teapot
17 bad_char chocolate_teapot
18 invalid_protocol chocolate_teapot
19 invalid_ipv4 chocolate_teapot
20 attribute_unrecognised invalid_ipv4 unrecognised_attribute chocolate_teapot
21 invalid_ipv4 chocolate_teapot
22 invalid_ipv6 chocolate_teapot
23 empty_ipv6 chocolate_teapot
24 malformed_ipv6 chocolate_teapot
25 invalid_ipv6 chocolate_teapot
26 invalid_protocol chocolate_teapot
27 bad_port chocolate_teapot
30 url_missing_username chocolate_teapot
31 url_empty_password url_missing_username chocolate_teapot
32 empty_host chocolate_teapot
33 url_empty_password ftp_protocol
34 url_empty_password empty_host chocolate_teapot
35 url_insecure_password ftp_protocol
41 chocolate_teapot

PASS ../toast/type/url/dubious.html
2 naughty_lang
11 unknown_protocol chocolate_teapot
12 url_insecure_password ftp_protocol

PASS ../toast/type/url/good.html
2 naughty_lang
19 character_code
28 ftp_protocol
29 ftp_protocol

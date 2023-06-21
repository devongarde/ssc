-N 1 -f ../toast/HTML/5.0/html5.conf

PASS ../toast/HTML/5.0/css-good.css
0 html
1 css_version
4 whatwg_class whatwg_class

PASS ../toast/HTML/5.0/css-good-too.css
0 html
1 css_version

PASS ../toast/HTML/5.0/example-1.html
2 naughty_lang
6 unrecognised_value
8 missing_close inserted_missing_closure

PASS ../toast/HTML/5.0/example-2.html
2 naughty_lang
6 unrecognised_value

PASS ../toast/HTML/5.0/example-3.html
0 title_required
2 inserted_missing_parent missing_close naughty_lang excluded_attribute excluded_attribute
5 url_not_found
6 url_not_found
7 url_not_found
8 excluded_attribute
12 url_not_found
13 url_not_found
14 url_not_found
19 excluded_attribute excluded_attribute excluded_attribute
21 excluded_attribute
23 excluded_attribute
28 excluded_attribute
35 excluded_attribute
36 excluded_attribute
38 url_not_found
39 url_not_found
40 url_not_found

PASS ../toast/HTML/5.0/example-4.html
0 title_required
2 inserted_missing_parent missing_close naughty_lang
7 url_not_found
9 only_elements
21 only_elements

PASS ../toast/HTML/5.0/example-5.html
0 title_required
2 inserted_missing_parent missing_close naughty_lang
14 missing_close
15 inserted_missing_closure
20 url_not_found
21 inserted_missing_closure missing_close url_not_found
22 inserted_missing_closure
31 use_quote_code
34 use_quote_code
41 missing_close url_not_found
42 inserted_missing_closure
55 use_quote_code
58 missing_close url_not_found
59 inserted_missing_closure
63 url_not_found
64 url_not_found
65 url_not_found

PASS ../toast/HTML/5.0/html5-bad.html
0 charset_mismatch charset_used charset_invalid
2 naughty_lang
5 bespoke_obsolete mime
7 only_once
10 default_role
14 unrecognised_value unrecognised_value deprecated_value deprecated_value
16 missing_close
18 lonely_ampersand inserted_missing_parent inserted_missing_closure inserted_missing_parent arg_count arg_count
19 inserted_missing_closure inserted_missing_closure missing_close
21 missing_open
23 unrecognised_value
31 mixed_mess
48 missing_open
49 missing_open
51 attribute_unrecognised unrecognised_attribute unrecognised_value
52 illegal_value
53 inserted_missing_closure
55 unrecognised_value
56 attributes_on_closure
57 unrecognised_value
58 attribute_required url_not_found naughty_alt
59 attribute_required url_not_found naughty_alt
60 attribute_required url_not_found naughty_alt
61 attribute_required url_not_found naughty_alt
62 attribute_required url_not_found naughty_alt
63 attribute_required url_not_found naughty_alt
65 missing_close inserted_missing_closure missing_open
77 url_not_found
80 value_ol url_not_found
81 inserted_missing_closure missing_close
82 inserted_missing_closure
85 use_quote_code
89 no_main_kids
90 no_main_kids
91 wrong_parent bad_ancestor
95 bad_descendant
97 bad_ancestor
109 no_dd
112 inserted_missing_closure
113 missing_open
115 url_not_found
116 url_not_found
117 url_not_found
118 url_not_found
119 url_not_found kind_media_srclang
122 url_not_found
123 url_not_found
124 url_not_found
125 url_not_found
126 url_not_found track_default
127 url_not_found track_default
128 url_not_found track_default
132 id_exists name_id
145 table_children
148 bad_descendant
153 1000
156 table_children
159 bad_descendant
164 1000
167 table_children
170 bad_descendant
175 1000
186 wrong_parent inserted_missing_closure
187 wrong_parent inserted_missing_closure
188 inserted_missing_closure inserted_missing_closure inserted_missing_closure missing_close
191 inserted_missing_closure
192 inserted_missing_closure
193 inserted_missing_closure wrong_parent inserted_missing_closure missing_close
194 bad_header_id bad_header_id
195 inserted_missing_closure
196 inserted_missing_closure missing_close
197 inserted_missing_closure inserted_missing_closure inserted_missing_closure
201 newline_in_string newline_in_string illegal_value
205 bad_meter
206 bad_meter
208 bad_meter
209 bad_meter bad_meter
210 bad_meter
211 bad_meter
213 bad_meter
214 bad_meter bad_meter bad_meter bad_meter bad_meter
217 url_not_found
218 bad_script bad_script
219 invalid_attribute_version wrong_version
220 script
221 script
222 script bad_script
223 script bad_script
224 script bad_script
225 script
226 unrecognised_value script
227 attribute_unrecognised_here unrecognised_attribute script
228 attribute_unrecognised_here unrecognised_attribute script

PASS ../toast/HTML/5.0/html5-bad-2.html
0 charset_mismatch charset_used charset_invalid
4 unrecognised_value
6 unrecognised_value

PASS ../toast/HTML/5.0/html5-example.html
2 naughty_lang
8 url_not_found
9 url_not_found
10 url_not_found
85 unrecognised_value
88 data_type attribute_required attribute_required attribute_required
98 url_not_found
104 use_quote_code
108 url_not_found
109 url_not_found
110 url_not_found
111 use_quote_code
117 url_not_found
120 url_not_found
121 inserted_missing_closure missing_close
122 inserted_missing_closure
125 use_quote_code
135 unrecognised_value
137 unrecognised_value
149 use_quote_code naughty_grave naughty_grave naughty_grave naughty_grave naughty_grave
151 use_double_quote_code
153 use_double_quote_code
156 schema_domain excluded_attribute excluded_attribute
158 excluded_attribute
159 excluded_attribute
163 use_quote_code
166 excluded_attribute
170 schema_domain excluded_attribute excluded_attribute
172 excluded_attribute
173 excluded_attribute
177 use_quote_code
181 schema_domain excluded_attribute excluded_attribute excluded_attribute
184 schema_domain excluded_attribute excluded_attribute excluded_attribute
185 excluded_attribute
187 excluded_attribute
191 schema_domain excluded_attribute excluded_attribute excluded_attribute
194 schema_domain excluded_attribute excluded_attribute excluded_attribute
195 excluded_attribute
197 excluded_attribute
241 url_not_found
244 url_not_found
246 no_such_folder url_not_found
248 use_double_quote_code
251 url_not_found
268 use_quote_code
271 use_quote_code
274 use_quote_code
276 use_quote_code
283 use_quote_code
320 url_id_unfound
322 missing_close unrecognised_value missing_close
323 inserted_missing_closure inserted_missing_closure
329 url_not_found
330 inserted_missing_closure url_not_found
331 inserted_missing_closure missing_close url_not_found
332 inserted_missing_closure
337 use_quote_code
343 attempted_escape
355 attempted_escape
360 no_such_folder url_not_found
361 no_such_folder url_not_found
378 url_not_found
379 url_not_found
389 no_such_folder url_not_found naughty_alt
391 no_such_folder url_not_found
392 no_such_folder url_not_found
393 attribute_required no_such_folder url_not_found naughty_alt
395 no_such_folder url_not_found
397 attribute_required no_such_folder url_not_found naughty_alt
399 use_quote_code no_such_folder url_not_found
402 url_not_found
403 inserted_missing_closure url_not_found
404 inserted_missing_closure missing_close url_not_found
405 inserted_missing_closure
408 url_not_found
412 attempted_escape no_such_folder url_not_found
413 attempted_escape no_such_folder url_not_found
414 url_not_found
467 inserted_missing_closure
468 use_quote_code
500 inserted_missing_closure
501 inserted_missing_closure missing_close
502 inserted_missing_closure
516 use_quote_code
544 use_quote_code
546 use_quote_code
555 use_quote_code
581 use_double_quote_code use_quote_code
588 use_double_quote_code
597 missing_close use_quote_code
600 inserted_missing_closure
602 use_double_quote_code
616 inserted_missing_closure
617 inserted_missing_closure
618 inserted_missing_closure missing_close
619 inserted_missing_closure
624 inserted_missing_closure
625 inserted_missing_closure
626 inserted_missing_closure missing_close
627 inserted_missing_closure
632 inserted_missing_closure
633 inserted_missing_closure
634 inserted_missing_closure missing_close
635 inserted_missing_closure
641 lingo
642 use_quote_code
670 use_quote_code
675 unrecognised_value use_quote_code
676 unrecognised_value
678 unrecognised_value use_quote_code
679 unrecognised_value
680 unrecognised_value
698 newline_in_string newline_in_string url_not_found
701 url_not_found url_not_found
703 use_quote_code
709 use_double_quote_code inserted_missing_closure
710 url_not_found
717 inserted_missing_closure
718 url_not_found
725 url_not_found
732 use_quote_code
743 use_quote_code
751 use_quote_code use_double_quote_code
753 use_double_quote_code
756 only_once
776 unrecognised_value
804 inserted_missing_parent missing_close
806 use_quote_code
822 inserted_missing_closure
823 inserted_missing_closure
824 inserted_missing_closure missing_close
825 inserted_missing_closure
836 use_double_quote_code
851 unrecognised_value
852 character_code
865 use_quote_code
868 use_quote_code
887 use_quote_code
900 use_double_quote_code use_quote_code
905 use_quote_code
911 use_quote_code
921 id_exists
939 naughty_grave
1010 schema_domain excluded_attribute excluded_attribute
1011 excluded_attribute
1012 excluded_attribute
1013 excluded_attribute
1016 excluded_attribute excluded_attribute
1017 excluded_attribute
1018 excluded_attribute
1019 excluded_attribute
1041 unrecognised_value
1061 use_quote_code
1067 use_quote_code
1071 use_quote_code
1073 unrecognised_value
1077 unrecognised_value unrecognised_value
1098 unrecognised_value
1116 use_quote_code
1117 unrecognised_value
1125 use_quote_code
1132 use_quote_code
1141 unrecognised_value unrecognised_value
1142 unrecognised_value
1143 unrecognised_value unrecognised_value
1144 unrecognised_value
1152 no_rp missing_close inserted_missing_closure
1154 no_rp inserted_missing_closure missing_close inserted_missing_closure
1156 no_rp no_rp
1157 no_rp no_rp
1158 no_rp no_rp
1160 no_rp no_rp no_rp
1161 no_rp
1162 no_rp no_rp
1164 no_rp missing_close inserted_missing_closure
1166 no_rp no_rp no_rp inserted_missing_closure inserted_missing_closure inserted_missing_closure inserted_missing_closure missing_close inserted_missing_closure
1168 no_rp no_rp inserted_missing_closure inserted_missing_closure missing_close inserted_missing_closure
1170 no_rp inserted_missing_closure inserted_missing_closure inserted_missing_closure inserted_missing_closure missing_close inserted_missing_closure
1172 no_rp no_rp no_rp no_rp inserted_missing_closure inserted_missing_closure inserted_missing_closure inserted_missing_closure inserted_missing_closure inserted_missing_closure missing_close inserted_missing_closure
1174 no_rp no_rp no_rp inserted_missing_closure inserted_missing_closure inserted_missing_closure inserted_missing_closure missing_close inserted_missing_closure missing_close inserted_missing_closure inserted_missing_closure
1176 no_rp no_rp no_rp no_rp no_rp no_rp
1177 inserted_missing_closure
1178 inserted_missing_closure
1179 inserted_missing_closure missing_close
1180 inserted_missing_closure
1182 no_rp no_rp no_rp no_rp no_rp no_rp
1188 no_rp
1197 no_rp no_rp no_rp no_rp no_rp
1205 inserted_missing_closure
1206 inserted_missing_closure missing_close
1207 inserted_missing_closure
1209 unrecognised_value unrecognised_value unrecognised_value unrecognised_value unrecognised_value
1210 unrecognised_value unrecognised_value lonely_ampersand unrecognised_value
1211 unrecognised_value unrecognised_value unrecognised_value unrecognised_value unrecognised_value
1212 lonely_ampersand unrecognised_value unrecognised_value unrecognised_value
1213 unrecognised_value
1220 chocolate_teapot
1221 chocolate_teapot
1227 use_double_quote_code use_double_quote_code
1265 use_quote_code
1291 use_quote_code
1295 use_quote_code
1313 no_such_folder url_not_found
1316 url_not_found
1317 no_such_folder url_not_found
1320 url_not_found
1332 url_not_found
1335 url_not_found
1337 url_not_found
1344 newline_in_string newline_in_string url_not_found
1349 naughty_alt
1355 overallowed
1357 url_not_found
1360 mime
1367 newline_in_string newline_in_string url_not_found
1372 url_not_found
1376 url_not_found mime
1377 url_not_found mime
1378 url_not_found mime
1379 url_not_found mime
1380 url_not_found mime
1381 url_not_found mime
1382 url_not_found mime
1383 url_not_found mime
1384 url_not_found mime
1385 url_not_found
1386 url_not_found
1387 url_not_found
1388 url_not_found mime
1391 url_not_found
1392 url_not_found
1393 url_not_found
1394 url_not_found
1395 url_not_found
1401 url_not_found
1404 url_not_found
1405 url_not_found
1406 url_not_found
1408 url_not_found
1418 use_quote_code
1421 inserted_missing_closure
1422 inserted_missing_closure
1423 inserted_missing_closure
1424 wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure
1425 inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure
1426 inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure
1427 inserted_missing_closure inserted_missing_closure inserted_missing_closure
1428 wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure
1429 inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure
1430 inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure
1431 inserted_missing_closure inserted_missing_closure inserted_missing_closure missing_close
1432 wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure
1433 inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure
1434 inserted_missing_closure wrong_parent inserted_missing_closure missing_close wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure missing_close
1435 inserted_missing_closure inserted_missing_closure inserted_missing_closure
1464 wild_attribute reputation wild_attribute url_not_found
1465 wild_attribute reputation wild_attribute attribute_barred url_not_found
1472 wrong_parent inserted_missing_closure
1473 wrong_parent inserted_missing_closure
1474 wrong_parent inserted_missing_closure
1475 inserted_missing_closure wrong_parent inserted_missing_closure
1477 wrong_parent inserted_missing_closure
1478 wrong_parent inserted_missing_closure
1479 wrong_parent inserted_missing_closure
1480 inserted_missing_closure inserted_missing_closure inserted_missing_closure missing_close
1483 wrong_parent inserted_missing_closure
1484 wrong_parent inserted_missing_closure attribute_required naughty_alt
1485 wrong_parent inserted_missing_closure
1486 inserted_missing_closure wrong_parent inserted_missing_closure missing_close
1488 wrong_parent inserted_missing_closure
1489 wrong_parent inserted_missing_closure
1490 wrong_parent inserted_missing_closure missing_close
1491 inserted_missing_closure inserted_missing_closure inserted_missing_closure
1492 url_not_found
1499 wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure wrong_parent inserted_missing_closure
1500 inserted_missing_closure inserted_missing_closure inserted_missing_closure
1501 inserted_missing_closure inserted_missing_closure wrong_parent inserted_missing_closure
1502 inserted_missing_closure wrong_parent inserted_missing_closure inserted_missing_closure inserted_missing_closure wrong_parent inserted_missing_closure
1503 inserted_missing_closure wrong_parent inserted_missing_closure missing_close inserted_missing_closure inserted_missing_closure wrong_parent inserted_missing_closure missing_close
1504 inserted_missing_closure inserted_missing_closure
1506 inserted_missing_closure inserted_missing_closure wrong_parent inserted_missing_closure
1507 inserted_missing_closure wrong_parent inserted_missing_closure inserted_missing_closure inserted_missing_closure wrong_parent inserted_missing_closure
1508 inserted_missing_closure wrong_parent inserted_missing_closure missing_close inserted_missing_closure inserted_missing_closure wrong_parent inserted_missing_closure missing_close
1509 inserted_missing_closure inserted_missing_closure
1520 wrong_parent inserted_missing_closure
1521 wrong_parent inserted_missing_closure
1522 inserted_missing_closure inserted_missing_closure inserted_missing_closure missing_close
1525 inserted_missing_closure
1526 inserted_missing_closure
1527 inserted_missing_closure wrong_parent inserted_missing_closure missing_close
1529 inserted_missing_closure
1530 inserted_missing_closure missing_close
1531 inserted_missing_closure inserted_missing_closure inserted_missing_closure
1533 url_not_found
1535 inserted_missing_closure
1539 inserted_missing_closure
1540 inserted_missing_closure
1541 inserted_missing_closure inserted_missing_closure
1543 inserted_missing_closure
1544 inserted_missing_closure
1545 inserted_missing_closure inserted_missing_closure missing_close
1547 inserted_missing_closure
1548 inserted_missing_closure missing_close
1549 inserted_missing_closure inserted_missing_closure
1551 inserted_missing_closure missing_close
1552 inserted_missing_closure
1554 url_not_found
1561 no_such_folder url_not_found
1562 no_such_folder url_not_found
1567 no_such_folder url_not_found
1568 no_such_folder url_not_found
1573 no_such_folder url_not_found
1574 no_such_folder url_not_found
1582 inserted_missing_closure

PASS ../toast/HTML/5.0/html5-good.html
2 naughty_lang
11 unrecognised_value unknown_rel link_rel_off
34 requires_href
38 url_not_found
58 lonely_radio
63 url_not_found naughty_alt
68 unrecognised_value
92 inserted_missing_closure
93 inserted_missing_closure inserted_missing_closure missing_close
94 inserted_missing_closure

PASS ../toast/HTML/5.0/html5-legacy.html
2 naughty_lang

PASS ../toast/HTML/5.0/html5-media.html
8 mq_syntax
20 unrecognised_value
21 correct_spelling unrecognised_value
22 unrecognised_value unrecognised_value
23 bad_media
25 bad_media

PASS ../toast/HTML/5.0/template-1.html
2 naughty_lang

PASS ../toast/HTML/5.0/template-2.html
2 naughty_lang

PASS ../toast/HTML/5.0/template-3.html
1 presume_html_1 attribute_unrecognised_here unrecognised_attribute

PASS ../toast/HTML/5.0/template-4.html
2 inserted_missing_parent missing_close naughty_lang inserted_missing_parent missing_close
4 inserted_missing_parent inserted_missing_closure missing_close

PASS ../toast/HTML/5.0/math-example-1.html
3 naughty_lang

CLASS
advertising 0 1
author 0 1
carpet 0 1
copyright 0 1
cursor 0 1
doris 13 0
dtend 0 1
dtstart 0 1
error 13 2
example 0 4
fire 0 1
h1class 13 0
ident 0 15
info 13 2
keyword 0 6
lang-c 0 1
language-pascal 0 1
lede 0 1
literal 0 1
location 0 1
part-of-speech 0 3
printable 9 0
prompt 0 2
pronunciation 0 2
spaceship 0 1
summary 0 1
taxonomy 0 1
title 0 1
twitter-tweet 0 1
type 0 1
url 0 1
vevent 0 1
warning 13 2

DCLASS
*.doris 1 0
*.error 1 0
*.h1class 1 0
*.info 1 0
*.printable 1 0
*.warning 1 0
a.url 0 1
aside.advertising 0 1
b.lede 0 1
blockquote.twitter-tweet 0 1
body.example 0 2
button.fire 0 1
cite.author 0 1
cite.title 0 1
code.lang-c 0 1
code.language-pascal 0 1
dd.part-of-speech 0 1
dd.pronunciation 0 2
div.example 0 2
div.spaceship 0 1
div.vevent 0 1
i.part-of-speech 0 2
i.taxonomy 0 1
input.carpet 0 1
p.copyright 0 1
span.cursor 0 1
span.error 0 1
span.ident 0 15
span.info 0 1
span.keyword 0 6
span.literal 0 1
span.location 0 1
span.prompt 0 2
span.summary 0 1
span.type 0 1
span.warning 0 1
time.dtend 0 1
time.dtstart 0 1

jID
c1 0 1
c2 0 1
comment-1 0 1
des 0 1
destroy 0 1
e1 0 1
e2 0 1
e3 0 1
e4 0 1
example 0 1
f 0 1
fish-caption 0 1
gdo 0 1
l4 0 1
map 0 1
msg1 0 1
msg2 0 1
msg3 0 1
n 0 2
plan 0 1
public 0 1
r1 0 2
r2 0 2
resultStats 0 1
summary 0 2
tiddles 0 1
whatwg 0 2
x 0 1
y 0 1

kID
a#tiddles 0 1
article#c1 0 1
article#c2 0 1
article#comment-1 0 1
dfn#gdo 0 1
dfn#whatwg 0 2
div#resultStats 0 1
figcaption#fish-caption 0 1
figure#l4 0 1
form#f 0 1
input#e1 0 1
input#e2 0 1
input#e3 0 1
input#e4 0 1
map#map 0 1
map#plan 0 1
p#des 0 1
p#summary 0 2
section#destroy 0 1
section#example 0 1
section#public 0 1
span#msg1 0 1
span#msg2 0 1
span#msg3 0 1
th#n 0 2
th#r1 0 2
th#r2 0 2
th#x 0 1
video#y 0 1

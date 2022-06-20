-f ../toast/shadow/copy/copy.conf

PASS ../toast/shadow/copy/html-bad.html
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
34 not_iso_8859_1
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
222 url_not_found script bad_script
223 url_not_found script bad_script
224 script bad_script
225 script
226 unrecognised_value script
227 attribute_unrecognised_here unrecognised_attribute script
228 attribute_unrecognised_here unrecognised_attribute script

PASS ../toast/shadow/copy/html-good.html
2 naughty_lang
6 url_not_found
11 unrecognised_value unknown_rel link_rel_off
34 requires_href
58 lonely_radio
63 naughty_alt
68 unrecognised_value
84 unrecognised_value
85 unrecognised_value
86 unrecognised_value
92 inserted_missing_closure
93 inserted_missing_closure inserted_missing_closure missing_close
94 inserted_missing_closure

PASS ../toast/shadow/copy/index.html
2 naughty_lang

PASS ../toast/shadow/copy/space.html
2 naughty_lang

PASS ../toast/shadow/copy/ssi.html
2 ssi
5 naughty_lang

shadow
0 shadow

EXPORTS
../toast/shadow/copy/html-bad.html.model ../toast/tmp/copy/html-bad.html
../toast/shadow/copy/html-good.html.model ../toast/tmp/copy/html-good.html
../toast/shadow/copy/index.html.model ../toast/tmp/copy/index.html
../toast/shadow/copy/space.html.model ../toast/tmp/copy/space.html
../toast/shadow/copy/ssi.html.model ../toast/tmp/copy/ssi.html

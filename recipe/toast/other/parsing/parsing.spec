-f ../toast/other/parsing/parsing.conf

PASS ../toast/other/parsing/comment.html
16 ssi
17 dashdash

PASS ../toast/other/parsing/doctype-missing.html
1 presume_html_1

PASS ../toast/other/parsing/elementerror.html
2 missing_close naughty_lang
11 unrecognised_value
13 mixed_mess mixed_mess
14 double_gin_and_tonic double_gin_and_tonic unrecognised_value
20 eof_in_element

PASS ../toast/other/parsing/index.html
2 naughty_lang

PASS ../toast/other/parsing/parsing-bad.html
2 missing_close naughty_lang
9 unrecognised_value double_gin_and_tonic
11 attribute_repeated attribute_repeated unrecognised_value unrecognised_value unrecognised_value
13 bizarre_character_code invalid_character_code denary_too_long mixed_mess
16 naked_grave missing_close
26 inserted_missing_closure
30 eof_in_cdata

PASS ../toast/other/parsing/person.html
12 sarcasm
13 fe
19 newline_in_string newline_in_string missing_double_quote missing_double_quote attribute_unrecognised attribute_unrecognised attribute_unrecognised attribute_repeated unrecognised_attribute unrecognised_attribute attribute_barred attribute_barred unrecognised_attribute invalid_attribute_version wrong_version missing_open missing_open

PASS ../toast/other/parsing/quotes.html
2 inserted_missing_parent naughty_lang
5 bad_script
14 attribute_unrecognised attribute_name_unexpected_character unrecognised_attribute
15 attribute_unrecognised attribute_name_unexpected_character unrecognised_attribute

PASS ../toast/other/parsing/scripts.html
2 naughty_lang
7 embedded_lingo
8 embedded_lingo
9 missing_double_quote

PASS ../toast/other/parsing/stringerror.html
2 missing_close naughty_lang
9 missing_close
13 mixed_mess mixed_mess
14 double_gin_and_tonic double_gin_and_tonic unrecognised_value
26 newline_in_string eof_in_element

PASS ../toast/other/parsing/ssi.html
2 naughty_lang
7 ssi

PASS ../toast/other/parsing/xhtml-xml.html
1 xhtml_1_0
4 rdfa_version

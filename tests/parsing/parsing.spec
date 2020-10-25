-f tests/parsing/parsing.conf

PASS tests/parsing/doctype-missing.html
1 presume_html_1

PASS tests/parsing/elementerror.html
2 missing_close naughty_lang
11 unrecognised_value
13 mixed_mess mixed_mess
14 double_gin_and_tonic double_gin_and_tonic unrecognised_value
20 eof_in_element

PASS tests/parsing/index.html
2 naughty_lang

PASS tests/parsing/parsing-bad.html
2 missing_close naughty_lang
9 unrecognised_value
11 attribute_repeated attribute_repeated unrecognised_value unrecognised_value unrecognised_value
13 bizarre_character_code invalid_character_code denary_too_long mixed_mess
17 double_gin_and_tonic
28 eof_in_cdata

PASS tests/parsing/quotes.html
2 inserted_missing_parent naughty_lang
7 use_double_quote_code inserted_missing_closure enquote_value enquote_value inserted_missing_closure
9 use_double_quote_code

PASS tests/parsing/scripts.html
2 naughty_lang
7 embedded_lingo
8 embedded_lingo
9 attribute_name_unexpected_character

PASS tests/parsing/stringerror.html
2 missing_close naughty_lang
9 missing_close
13 mixed_mess mixed_mess
14 double_gin_and_tonic double_gin_and_tonic unrecognised_value
26 newline_in_string eof_in_element

PASS tests/parsing/ssi.html
2 naughty_lang
7 ssi

PASS tests/parsing/xhtml-xml.html
1 xhtml_1_0

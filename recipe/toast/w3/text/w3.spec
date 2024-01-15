-Y 1 -f ../toast/w3/text/w3.conf

PASS ../toast/w3/text/index.html
2 naughty_lang

PASS ../toast/w3/text/texthtml_nocharset-utf8.html
0 charset_mismatch charset_used
1 xhtml_1_0
14 missing_close
16 inserted_missing_closure

PASS ../toast/w3/text/texthtml_nocharset.html
1 xhtml_1_0

PASS ../toast/w3/text/texthtml_nodoctype.html.utf8
1 presume_html_1
7 attribute_unrecognised_here unrecognised_attribute

PASS ../toast/w3/text/texthtml_unknownparsemode.html.utf8
0 html_unknown_sgml

PASS ../toast/w3/text/textxml_html401.xml
2 html_superseded
3 inserted_missing_parent

PASS ../toast/w3/text/textxml_nocharset.xml
1 xhtml_1_0
12 use_double_quote_code

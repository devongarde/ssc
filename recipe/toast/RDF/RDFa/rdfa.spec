-f ../toast/RDF/RDFa/rdfa.conf

PASS ../toast/RDF/RDFa/index.html
2 naughty_lang

PASS ../toast/RDF/RDFa/rdf1-example.html
2 naughty_lang
27 rdfa_redefine

PASS ../toast/RDF/RDFa/rdf2-example.html
4 rdfa_redefine rdfa_redefine naughty_lang
22 unrecognised_value unknown_rel

PASS ../toast/RDF/RDFa/rdf3-example.html
0 charset_mismatch charset_used charset_invalid
5 rdfa_redefine naughty_lang

PASS ../toast/RDF/RDFa/rdf4-example.html
0 charset_mismatch charset_used charset_invalid
5 rdfa_redefine naughty_lang

PASS ../toast/RDF/RDFa/rdf5-example.html
0 charset_mismatch charset_used charset_invalid
2 naughty_lang

PASS ../toast/RDF/RDFa/rdfa-bad.html
2 naughty_lang
19 prefix_odd
21 prefix_format rdf_confusion prefix_format
23 prefix_format

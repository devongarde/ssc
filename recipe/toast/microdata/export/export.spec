-N 1 -f ../toast/microdata/export/export.conf

PASS ../toast/microdata/export/h-card.html
0 write_wrote
13 missing_open

PASS ../toast/microdata/export/index.html
0 export_none

PASS ../toast/microdata/export/itemref.html
0 write_wrote
15 missing_itemtype
27 missing_close
32 url_id_unfound
35 inserted_missing_closure

PASS ../toast/microdata/export/md-ref.html
0 write_wrote
14 not_ontology_property not_ontology_property
18 missing_itemtype
24 missing_itemtype

PASS ../toast/microdata/export/vcard.html
0 write_wrote
13 url_not_found naughty_alt
34 use_quote_code

PASS ../toast/microdata/export/vevent.html
0 write_wrote
27 use_quote_code

PASS ../toast/microdata/export/work.html
0 write_wrote
2 naughty_lang
8 attribute_required naughty_alt
11 missing_close
17 inserted_missing_closure

EXPORTS
../toast/microdata/export/h-card.html.model ../toast/tmp/export/h-card.html.json
../toast/microdata/export/itemref.html.model ../toast/tmp/export/itemref.html.json
../toast/microdata/export/md-ref.html.model ../toast/tmp/export/md-ref.html.json
../toast/microdata/export/vcard.html.model ../toast/tmp/export/vcard.html.json
../toast/microdata/export/vevent.html.model ../toast/tmp/export/vevent.html.json
../toast/microdata/export/work.html.model ../toast/tmp/export/work.html.json

Exports
0 shadow

Itemid
#mozOrg

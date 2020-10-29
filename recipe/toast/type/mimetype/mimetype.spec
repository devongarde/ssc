-f ../toast/type/mimetype/mimetype.conf

PASS ../toast/type/mimetype/index.html
2 naughty_lang

PASS ../toast/type/mimetype/bad.html
2 naughty_lang
12 not_img
13 mime bad_srcset saucy_source
15 mime bad_srcset saucy_source

PASS ../toast/type/mimetype/dubious.html
2 naughty_lang
12 not_img not_img
13 mime bad_srcset saucy_source
15 bad_srcset saucy_source
16 mime bad_srcset saucy_source

PASS ../toast/type/mimetype/good.html
2 naughty_lang
12 bad_srcset saucy_source
13 bad_srcset saucy_source

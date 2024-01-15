-Y 1 -f ../toast/type/httpequiv/httpequiv.conf

PASS ../toast/type/httpequiv/accept.html
2 naughty_lang
5 out_of_scope
6 out_of_scope 
7 out_of_scope 
8 out_of_scope 
9 out_of_scope 
10 out_of_scope 

PASS ../toast/type/httpequiv/bad.html
2 naughty_lang
5 out_of_scope
6 out_of_scope

PASS ../toast/type/httpequiv/cache.html
2 naughty_lang
5 unrecognised_value bad_cache
7 bad_cache
10 unrecognised_value bad_cache

PASS ../toast/type/httpequiv/cookie.html
2 naughty_lang
5 unrecognised_value
9 bad_cookie

PASS ../toast/type/httpequiv/corp.html
2 naughty_lang

PASS ../toast/type/httpequiv/index.html
2 naughty_lang
5 unrecognised_value
6 isnt

PASS ../toast/type/httpequiv/link.html
2 naughty_lang
5 empty
6 empty
7 too_many
8 nocando
9 too_many
10 too_many too_many
11 nocando
15 unrecognised_value
16 bad_link_pragma unrecognised_value

PASS ../toast/type/httpequiv/origin.html
2 naughty_lang
7 bad_root
8 bad_root

PASS ../toast/type/httpequiv/referrer.html
2 naughty_lang
5 empty_link

PASS ../toast/type/httpequiv/rp.html
2 naughty_lang
7 unrecognised_value

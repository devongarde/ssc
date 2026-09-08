-Y 1 -7 original -f ../toast/other/vtt/vtt.conf

PASS ../toast/other/vtt/bad1.vtt
0 webvtt webvtt
 
PASS ../toast/other/vtt/bad2.vtt
9 vtt_heirarchy
26 vtt_css
 
PASS ../toast/other/vtt/bad3.vtt
4 vtt_region_value unrecognised_value vtt_region
10 percent
19 vtt_region_value vtt_region vtt_region_id
23 unrecognised_value vtt_cue
26 vtt_timestamp vtt_region
29 vtt_region

PASS ../toast/other/vtt/ex6.vtt
4 vtt_class vtt_class

PASS ../toast/other/vtt/ex8.vtt
19 vtt_region
22 vtt_region
25 vtt_region
28 vtt_region
31 vtt_region

PASS ../toast/other/vtt/ex22g.vtt
7 unrecognised_value vtt_cue

PASS ../toast/other/vtt/ex22i.vtt
4 vtt_region vtt_region unrecognised_value
10 vtt_region vtt_region unrecognised_value
19 vtt_region 

PASS ../toast/other/vtt/ex22c.css
1 selector

PASS ../toast/other/vtt/ex22e.css
9 css_syntax pseud

PASS ../toast/other/vtt/ex2.html
2 naughty_lang
16 url_not_found track_missing track_missing autoplay
17 url_not_found

PASS ../toast/other/vtt/ex21.html
2 inserted_missing_parent missing_close naughty_lang inserted_missing_parent missing_close
3 inserted_missing_parent inserted_missing_closure missing_close url_not_found track_missing track_missing autoplay
4 url_not_found

PASS ../toast/other/vtt/ex22e.html
2 inserted_missing_parent missing_close naughty_lang inserted_missing_parent missing_close
3 inserted_missing_parent inserted_missing_closure missing_close track_missing track_missing
5 url_not_found

PASS ../toast/other/vtt/index.html
2 naughty_lang

GRAND
Class:
  bg_blue declared never, used once
  first declared never, used once
  lime declared never, used once
  loud declared twice, used once
  yellow declared never, used once

Nits Reported:
    Abhorrences: twice
    Errors: 28fold
    Warnings: 35fold

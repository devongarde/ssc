-N 1 -f ../toast/other/CSS/css.conf

PASS ../toast/other/CSS/css-bad.html
2 naughty_lang
5 url_not_found
8 attribute_unrecognised unrecognised_attribute
10 unrecognised_value
12 unrecognised_value
16 unrecognised_value

PASS ../toast/other/CSS/css-dubious.html
2 naughty_lang
8 unrecognised_value
10 unrecognised_value
12 unrecognised_value
16 unrecognised_value
17 unrecognised_value

PASS ../toast/other/CSS/css-empty.html
2 naughty_lang
10 unrecognised_value

PASS ../toast/other/CSS/css-good.html
2 naughty_lang
10 unrecognised_value
12 unrecognised_value

GRAND
Elements:
    !doctype: 5 times 
    body: 5 times 
      class: once 
    data: 4 times 
      class: 4 times 
      value: 4 times 
    h1: 4 times 
      class: 4 times 
    head: 5 times 
    html: 5 times 
      lang: once 
    link: 4 times 
      href: 4 times 
      rel: 4 times 
      type: 4 times 
    p: once 
    slot: twice 
      class: twice 
    title: 5 times 
  Attribute counts:
    class: 11 times 
    href: 4 times 
    lang: once 
    rel: 4 times 
    type: 4 times 
    value: 4 times 
  13 elements used 111 times
CSS class(es):
    bodyclass: 0
    boing: 0
    doris: 0
    h1class: 0
    h2class: 0
    pclass: 0
    sid: 0
    test: 0
  8 class(es) used 0 times
CSS element.class(es):
    body.bodyclass: 0
    data.boing: 0
    data.doris: 0
    data.sid: 0
    h1.h1class: 0
    h1.h2class: 0
    h1.pclass: 0
    slot.test: 0
  8 element.class(es) used 0 times
Nits Reported:
    Errors: once 
    Warnings: 17 times 
  
Nit Categories:
    Attribute: 6 times 
    Type: 11 times 
    URx: once 
  
References:
    HTML 5.0: 4 times 
  
Versions:
    HTML5/20210101/SVG-2.0/MathML-4(Dec20)/CSS-1/WhatWG: 5 times 
  
File info:
     1620 bytes read in 8 files, with an average of roughly 203 bytes per file
     smallest file: 0 bytes, largest file: 365 bytes
===

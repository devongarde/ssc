-N 1 -f ../toast/other/CSS/css.conf

PASS ../toast/other/CSS/css-bad.html
2 naughty_lang
5 url_not_found url_not_found
8 attribute_unrecognised unrecognised_attribute
10 unrecognised_value
12 unrecognised_value
16 unrecognised_value

PASS ../toast/other/CSS/css-dubious.html
2 naughty_lang
5 bad_classname class_microformat_property class_microformat_vocabulary class_microformat_property class_microformat_vocabulary
8 unrecognised_value
10 unrecognised_value
12 unrecognised_value
16 unrecognised_value

PASS ../toast/other/CSS/css-empty.html
2 naughty_lang
10 unrecognised_value

PASS ../toast/other/CSS/css-good.html
2 naughty_lang

GRAND
Elements:
    !doctype: 4 times 
    body: 4 times 
      class: once 
    data: 4 times 
      class: 4 times 
      value: 4 times 
    h1: 4 times 
      class: 4 times 
    head: 4 times 
    html: 4 times 
    link: 4 times 
      href: 4 times 
      rel: 4 times 
      type: 4 times 
    slot: twice 
      class: twice 
    title: 4 times 
  Attribute counts:
    class: 11 times 
    href: 4 times 
    rel: 4 times 
    type: 4 times 
    value: 4 times 
  12 elements used 94 times

class CSS/HTML:
  "footnote": 1/0
  "h1class": 1/0
  "min-width": 2/0
  "weather": 1/0
  4x class: 5/0

element.class CSS/HTML:
  ".footnote": 1/0
  ".footnote.min-width": 1/0
  ".h1class": 1/0
  ".h1class.min-width": 1/0
  "??:.weather": 1/0
  5x element.class: 5/0
Nits Reported:
    Errors: once 
    Warnings: 18 times 
  
Nit Categories:
    Attribute: 6 times 
    Spelling: once 
    Type: 11 times 
    URx: once 
  
References:
    HTML 5.0: 4 times 
  
Versions:
    HTML5/20210101/SVG-2.0/MathML-4(Dec20)/WhatWG: 4 times 
  
File info:
     1479 bytes read in 7 HTML files, with an average of roughly 211 bytes per file
     smallest file: 0 bytes, largest file: 365 bytes
 ===

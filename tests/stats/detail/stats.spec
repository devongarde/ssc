-f tests/stats/detail/stats.conf

PASS tests/stats/detail/index.html
2 naughty_lang

STATS
Elements:
    !doctype: once
    body: once
    h1: once
    head: once
    html: once
    p: once
    title: once
  10 elements used 20 times
No errors or warnings

PASS tests/stats/detail/itemref.html
27 missing_close
32 url_id_unfound
35 inserted_missing_closure

STATS
Elements:
    !doctype: once
    body: once
    div: 7 times
      id: thrice
      itemid: once
      itemprop: once
      itemref: thrice
      itemscope: 6 times
      itemtype: thrice
    h1: once
    head: once
    html: once
      lang: once
    link: once
      href: once
      itemprop: once
    p: thrice
      id: once
    span: 4 times
      id: once
      itemprop: 4 times
    title: once
  Attribute counts:
    href: used once
    id: used 5 times
    itemid: used once
    itemprop: used 6 times
    itemref: used thrice
    itemscope: used 6 times
    itemtype: used thrice
    lang: used once
  13 elements used 60 times
Microdata:
    BlogPosting: twice
      commentCount: once
      name: once
      publisher: once
    Organization: once
  Property counts:
    commentCount: used once
    name: used once
    publisher: used once
  2 itemtypes used thrice
No errors or warnings

PASS tests/stats/detail/md-ref.html
14 not_schema_property not_schema_property

STATS
Elements:
    !doctype: once
    body: once
    div: thrice
      hidden: once
      id: once
      itemprop: twice
      itemscope: twice
      itemtype: twice
    h1: once
    head: once
    html: once
      lang: once
    link: thrice
      href: thrice
      itemprop: thrice
    meta: 7 times
      content: 5 times
      itemprop: 7 times
      itemref: twice
      itemscope: twice
      itemtype: twice
    title: once
  Attribute counts:
    content: used 5 times
    hidden: used once
    href: used thrice
    id: used once
    itemprop: used 12 times
    itemref: used twice
    itemscope: used 4 times
    itemtype: used 4 times
    lang: used once
  12 elements used 46 times
Microdata:
    Organization: twice
      name: twice
      url: twice
    Person: twice
      description: twice
      name: twice
      url: twice
  Property counts:
    description: used twice
    name: used 4 times
    url: used 4 times
  2 itemtypes used 4 times
No errors or warnings

itemid
#mozOrg

GRAND
Elements:
    !doctype: thrice
    body: thrice
    div: 10 times
      hidden: once
      id: 4 times
      itemid: once
      itemprop: thrice
      itemref: thrice
      itemscope: 8 times
      itemtype: 5 times
    h1: thrice
    head: thrice
    html: thrice
      lang: twice
    link: 4 times
      href: 4 times
      itemprop: 4 times
    meta: 7 times
      content: 5 times
      itemprop: 7 times
      itemref: twice
      itemscope: twice
      itemtype: twice
    p: 4 times
      id: once
    span: 4 times
      id: once
      itemprop: 4 times
    title: thrice
  Attribute counts:
    content: used 5 times
    hidden: used once
    href: used 4 times
    id: used 6 times
    itemid: used once
    itemprop: used 18 times
    itemref: used 5 times
    itemscope: used 10 times
    itemtype: used 7 times
    lang: used twice
  14 elements used 126 times
Microdata:
    BlogPosting: twice
      commentCount: once
      name: once
      publisher: once
    Organization: thrice
      name: twice
      url: twice
    Person: twice
      description: twice
      name: twice
      url: twice
  Property counts:
    commentCount: used once
    description: used twice
    name: used 5 times
    publisher: used once
    url: used 4 times
  3 itemtypes used 7 times
Errors:
  Severity:
    Errors: 4 times
    Warnings: twice
  Categories:
    Attribute: once
    Element: 5 times
    Microdata: 10 times
    Parser: thrice
    URx: once
  References:
    HTML 5.0: 4 times
Versions:
  HTML5:200721/SVG-1.1/MathML-4/WhatWG: 3
File info:
  2096 bytes read in 3 HTML files with an average of 698.66666666666663 bytes per file
  smallest file: 120 bytes, largest file: 1019 bytes
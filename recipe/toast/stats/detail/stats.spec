-f ../toast/stats/detail/stats.conf

PASS ../toast/stats/detail/index.html
2 naughty_lang

STATS
Elements:
    !doctype: once
    body: once
    h1: once
    head: once
    html: once
    meta: thrice
      content: thrice
      name: thrice
    p: once
    title: once
  Attribute counts:
    content: used thrice
    name: used thrice
  11 elements used 26 times
Metadata:
  name:
    description: once
    author:
      sid: once
    generator:
      notepad: once
No errors or warnings

PASS ../toast/stats/detail/itemref.html
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

PASS ../toast/stats/detail/keyword-1.html
2 naughty_lang

STATS
Elements:
    !doctype: once
    body: once
    h1: once
    head: once
    html: once
    meta: 4 times
      content: 4 times
      http-equiv: once
      name: thrice
    title: once
  Attribute counts:
    content: used 4 times
    http-equiv: used once
    name: used thrice
  10 elements used 25 times
Metadata:
  pragma:
    refresh: once
    author:
      doris: once
    keywords:
      a: once
      b: once
      c: once
No errors or warnings

PASS ../toast/stats/detail/keyword-2.html
2 naughty_lang

STATS
Elements:
    !doctype: once
    body: once
    h1: once
    head: once
    html: once
    meta: 4 times
      content: 4 times
      http-equiv: once
      name: thrice
    title: once
  Attribute counts:
    content: used 4 times
    http-equiv: used once
    name: used thrice
  10 elements used 25 times
Metadata:
  pragma:
    content-security-policy: once
    author:
      doris: once
    generator:
      beer: once
    keywords:
      a: once
      d: once
No errors or warnings

PASS ../toast/stats/detail/md-ref.html
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
    !doctype: 5 times
    body: 5 times
    div: 10 times
      hidden: once
      id: 4 times
      itemid: once
      itemprop: thrice
      itemref: thrice
      itemscope: 8 times
      itemtype: 5 times
    h1: 5 times
    head: 5 times
    html: 5 times
      lang: twice
    link: 4 times
      href: 4 times
      itemprop: 4 times
    meta: 18 times
      content: 16 times
      http-equiv: twice
      itemprop: 7 times
      itemref: twice
      itemscope: twice
      itemtype: twice
      name: 9 times
    p: 4 times
      id: once
    span: 4 times
      id: once
      itemprop: 4 times
    title: 5 times
  Attribute counts:
    content: used 16 times
    hidden: used once
    href: used 4 times
    http-equiv: used twice
    id: used 6 times
    itemid: used once
    itemprop: used 18 times
    itemref: used 5 times
    itemscope: used 10 times
    itemtype: used 7 times
    lang: used twice
    name: used 9 times
  14 elements used 182 times
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
Metadata:
  pragma:
    content-security-policy: once
    refresh: once
  name:
    description: once
    author:
      doris: twice
      sid: once
    generator:
      beer: once
      notepad: once
    keywords:
      a: twice
      b: once
      c: once
      d: once
Errors:
  Severity:
    Errors: 4 times
    Warnings: 4 times
  Categories:
    Attribute: thrice
    Element: 7 times
    Microdata: 10 times
    Parser: 5 times
    URx: once
  References:
    HTML 5.0: 8 times
Versions:
  HTML5/20210101/SVG-2.0/MathML-3/WhatWG: 5
File info:
  2809 bytes read in 5 HTML files with an average of 561.79999999999995 bytes per file
  smallest file: 259 bytes, largest file: 1019 bytes

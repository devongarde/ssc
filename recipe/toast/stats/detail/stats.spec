-Y 1 -f ../toast/stats/detail/stats.conf

PASS ../toast/stats/detail/extra.html
14 unrecognised_value
18 unrecognised_value
22 unrecognised_value

STATS
Class:
  goodbye styled 0 times, used once
  hello styled 0 times, used once
  kitty styled 0 times, used once

Class/Element:
  p.goodbye styled 0 times, used once
  p.hello styled 0 times, used once
  p.kitty styled 0 times, used once

Element:
    !doctype: once
    body: once
    h1: once
    head: once
    html: once
      lang: once
    p: thrice
      class: thrice
    title: once
  Attribute count:
    class: thrice
    lang: once
  10 elements used 27 times
===

PASS ../toast/stats/detail/index.html
2 naughty_lang

STATS
Element:
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
  Attribute count:
    content: thrice
    name: thrice
  11 elements used 26 times

Header:
  metadata:
    description: once
  name:
    author:
      sid: once
    generator:
      notepad: once
===

PASS ../toast/stats/detail/itemref.html
15 missing_itemtype
27 missing_close
32 url_id_unfound
35 inserted_missing_closure

STATS
Element:
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
  Attribute count:
    href: once
    id: 5 times
    itemid: once
    itemprop: 6 times
    itemref: thrice
    itemscope: 6 times
    itemtype: thrice
    lang: once
  13 elements used 60 times

Id:
  a styled 0 times, used once
  amanda styled 0 times, used once
  b styled 0 times, used once
  c styled 0 times, used once
  comments styled 0 times, used once

Id/Element:
  div#amanda styled 0 times, used once
  div#b styled 0 times, used once
  div#c styled 0 times, used once
  p#a styled 0 times, used once
  span#comments styled 0 times, used once

ItemId:
    a: 0
    amanda: 0
    b: 0
    c: 0
    comments: 0
  5 ItemId used 0 times

Ontology:
    http://schema.org/BlogPosting: twice
      commentCount: once
      name: once
      publisher: once
    http://schema.org/Organization: once
  Property counts:
    commentCount: once
    name: once
    publisher: once
  2 itemtypes used thrice
===

PASS ../toast/stats/detail/keyword-1.html
2 naughty_lang

STATS
Abbreviation:
    CFL: once, "Chemin de Fer Luxembourg"

Definition:
    Chemin de Fer Luxembourg: once, "CFL operates trains."
    FRED: once, "File Retrieval Encoding and Decoding"
    PKI: once, "The Public Key Infrastructure distributes trust online."
    Tiddles: once, "The tortoiseshell Tiddles is a rather affectionate cat."
    Tiddles: once, "Tiddles, no siamese, likes to miaow."

Element:
    !doctype: once
    abbr: once
      title: once
    body: once
    dfn: 5 times
      title: twice
    h1: once
    head: once
    html: once
    meta: 4 times
      content: 4 times
      http-equiv: once
      name: thrice
    p: 5 times
    span: once
    title: once
  Attribute count:
    content: 4 times
    http-equiv: once
    name: thrice
    title: thrice
  14 elements used 54 times

Header:
  pragma:
    Refresh: once
  name:
    author:
      doris: once
    keywords:
      a: once
      b: once
      c: once
===

PASS ../toast/stats/detail/keyword-2.html
2 naughty_lang

STATS
Abbreviation:
    DP: once, "Demokratesch Partei"

Element:
    !doctype: once
    abbr: once
      title: once
    body: once
    dd: 7 times
    dl: once
    dt: 8 times
    h1: once
    head: once
    html: once
    meta: 4 times
      content: 4 times
      http-equiv: once
      name: thrice
    p: once
      lang: once
    title: once
  Attribute count:
    content: 4 times
    http-equiv: once
    lang: once
    name: thrice
    title: once
  16 elements used 82 times

Header:
  pragma:
    Content-Security-Policy: once
  name:
    author:
      doris: once
    generator:
      beer: once
    keywords:
      a: once
      d: once

Name/Value Pair:
    bread and cheese: once, "in Dutch hotel breakfast"
    bread and cheese: once, "in Flemish hotel breakfast"
    coffee: once, "in hotel continental breakfast"
    corn flakes: once, "as tasty and as nutritional as cardboard"
    croissant: once, "in hotel continental breakfast"
    egg: once, "in English breakfast"
    egg: once, "in Irish breakfast"
    fried bread: twice, "in English breakfast"
    fried bread: once, "in Irish breakfast"
    sausage: once, "in English breakfast"
    sausage: once, "in Irish breakfast"
===

PASS ../toast/stats/detail/md-ref.html
14 not_ontology_property not_ontology_property
18 missing_itemtype
24 missing_itemtype

STATS
Element:
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
  Attribute count:
    content: 5 times
    hidden: once
    href: thrice
    id: once
    itemprop: 12 times
    itemref: twice
    itemscope: 4 times
    itemtype: 4 times
    lang: once
  12 elements used 46 times

Id:
  tid styled 0 times, used once

Id/Element:
  div#tid styled 0 times, used once

ItemId:
    tid: 0
  1 ItemId used 0 times

Ontology:
    http://schema.org/Organization: twice
      founder: twice
      name: twice
      url: twice
    http://schema.org/Person: twice
      description: twice
      name: twice
      url: twice
  Property counts:
    description: twice
    founder: twice
    name: 4 times
    url: 4 times
  2 itemtypes used 4 times
===

itemids
#mozOrg

GRAND
Abbreviation:
    CFL: once, "Chemin de Fer Luxembourg"
    DP: once, "Demokratesch Partei"

Category:
    Attribute: thrice
    Element: twice
    Schema: 5 times
    Type: thrice
    URx: once

Class:
  goodbye styled 0 times, used once
  hello styled 0 times, used once
  kitty styled 0 times, used once

Class/Element:
  p.goodbye styled 0 times, used once
  p.hello styled 0 times, used once
  p.kitty styled 0 times, used once

Definition:
    Chemin de Fer Luxembourg: once, "CFL operates trains."
    FRED: once, "File Retrieval Encoding and Decoding"
    PKI: once, "The Public Key Infrastructure distributes trust online."
    Tiddles: once, "The tortoiseshell Tiddles is a rather affectionate cat."
    Tiddles: once, "Tiddles, no siamese, likes to miaow."

Element:
    !doctype: 6 times
    abbr: twice
      title: twice
    body: 6 times
    dd: 7 times
    dfn: 5 times
      title: twice
    div: 10 times
      hidden: once
      id: 4 times
      itemid: once
      itemprop: thrice
      itemref: thrice
      itemscope: 8 times
      itemtype: 5 times
    dl: once
    dt: 8 times
    h1: 6 times
    head: 6 times
    html: 6 times
      lang: thrice
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
    p: 13 times
      class: thrice
      id: once
      lang: once
    span: 5 times
      id: once
      itemprop: 4 times
    title: 6 times
  Attribute count:
    class: thrice
    content: 16 times
    hidden: once
    href: 4 times
    http-equiv: twice
    id: 6 times
    itemid: once
    itemprop: 18 times
    itemref: 5 times
    itemscope: 10 times
    itemtype: 7 times
    lang: 4 times
    name: 9 times
    title: 4 times
  20 elements used 295 times

Nits Reported:
    Errors: 4 times
    Warnings: 9 times
    Info: once

File Info:
    4025 bytes read in 6 files, with an average of roughly 671 bytes per file
    smallest file: 252 bytes, largest file: 1019 bytes

Id:
  a styled 0 times, used once
  amanda styled 0 times, used once
  b styled 0 times, used once
  c styled 0 times, used once
  comments styled 0 times, used once
  tid styled 0 times, used once

Id/Element:
  div#amanda styled 0 times, used once
  div#b styled 0 times, used once
  div#c styled 0 times, used once
  div#tid styled 0 times, used once
  p#a styled 0 times, used once
  span#comments styled 0 times, used once

ItemId:
    a: 0
    amanda: 0
    b: 0
    c: 0
    comments: 0
    tid: 0
  6 ItemId used 0 times

Header:
  pragma:
    Content-Security-Policy: once
    Refresh: once
  metadata:
    description: once
  name:
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

Ontology:
    http://schema.org/BlogPosting: twice
      commentCount: once
      name: once
      publisher: once
    http://schema.org/Organization: thrice
      founder: twice
      name: twice
      url: twice
    http://schema.org/Person: twice
      description: twice
      name: twice
      url: twice
  Property counts:
    commentCount: once
    description: twice
    founder: twice
    name: 5 times
    publisher: once
    url: 4 times
  3 itemtypes used 7 times

Reference:
    HTML 5.0: thrice
    WhatWG HTML 5, Jul 20: thrice
    HTML 5, Jul 23: twice

Name/Value Pair:
    bread and cheese: once, "in Dutch hotel breakfast"
    bread and cheese: once, "in Flemish hotel breakfast"
    coffee: once, "in hotel continental breakfast"
    corn flakes: once, "as tasty and as nutritional as cardboard"
    croissant: once, "in hotel continental breakfast"
    egg: once, "in English breakfast"
    egg: once, "in Irish breakfast"
    fried bread: twice, "in English breakfast"
    fried bread: once, "in Irish breakfast"
    sausage: once, "in English breakfast"
    sausage: once, "in Irish breakfast"

Version:
    HTML-5/20210101/SVG-2.0/MathML-4(Dec20)/CSS-2.1/WhatWG: 6 times
===

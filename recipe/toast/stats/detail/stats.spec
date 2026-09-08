-Y 1 -7 original -f ../toast/stats/detail/stats.conf

PASS ../toast/stats/detail/extra.html
14 unrecognised_value
18 unrecognised_value
22 unrecognised_value

STATS
Class:
  goodbye declared never, used once
  hello declared never, used once
  kitty declared never, used once

Class/Element:
  p.goodbye declared never, used once
  p.hello declared never, used once
  p.kitty declared never, used once

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
  10 elements used 27fold
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
  11 elements used 26fold

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
27 missing_close
32 url_id_unfound
35 inserted_missing_closure

STATS
Element:
    !doctype: once
    body: once
    div: sevenfold
      id: thrice
      itemid: once
      itemprop: once
      itemref: thrice
      itemscope: sixfold
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
    span: fourfold
      id: once
      itemprop: fourfold
    title: once
  Attribute count:
    href: once
    id: fivefold
    itemid: once
    itemprop: sixfold
    itemref: thrice
    itemscope: sixfold
    itemtype: thrice
    lang: once
  13 elements used 60fold

Id:
  a declared never, used once
  amanda declared never, used once
  b declared never, used once
  c declared never, used once
  comments declared never, used once

Id/Element:
  div#amanda declared never, used once
  div#b declared never, used once
  div#c declared never, used once
  p#a declared never, used once
  span#comments declared never, used once

ItemId:
    a: never
    amanda: never
    b: never
    c: never
    comments: never
  5 ItemId used never

Ontology:
    http://schema.org/BlogPosting: twice
      publisher: once
    http://schema.org/Organization: once
  Property counts:
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
    dfn: fivefold
      title: twice
    h1: once
    head: once
    html: once
    meta: fourfold
      content: fourfold
      http-equiv: once
      name: thrice
    p: fivefold
    span: once
    title: once
  Attribute count:
    content: fourfold
    http-equiv: once
    name: thrice
    title: thrice
  14 elements used 54fold

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
    dd: sevenfold
    dl: once
    dt: eightfold
    h1: once
    head: once
    html: once
    meta: fourfold
      content: fourfold
      http-equiv: once
      name: thrice
    p: once
      lang: once
    title: once
  Attribute count:
    content: fourfold
    http-equiv: once
    lang: once
    name: thrice
    title: once
  16 elements used 82fold

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
18 no_itemscope
24 no_itemscope

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
    meta: sevenfold
      content: fivefold
      itemprop: sevenfold
      itemref: twice
      itemscope: twice
      itemtype: twice
    title: once
  Attribute count:
    content: fivefold
    hidden: once
    href: thrice
    id: once
    itemprop: twelvefold
    itemref: twice
    itemscope: fourfold
    itemtype: fourfold
    lang: once
  12 elements used 46fold

Id:
  tid declared never, used once

Id/Element:
  div#tid declared never, used once

ItemId:
    tid: never
  1 ItemId used never

Ontology:
    http://schema.org/Organization: twice
      founder: twice
      name: twice
      url: twice
    http://schema.org/Person: twice
  Property counts:
    founder: twice
    name: twice
    url: twice
  2 itemtypes used fourfold
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
    Microdata: twice
    Type: thrice
    URx: once

Class:
  goodbye declared never, used once
  hello declared never, used once
  kitty declared never, used once

Class/Element:
  p.goodbye declared never, used once
  p.hello declared never, used once
  p.kitty declared never, used once

Definition:
    Chemin de Fer Luxembourg: once, "CFL operates trains."
    FRED: once, "File Retrieval Encoding and Decoding"
    PKI: once, "The Public Key Infrastructure distributes trust online."
    Tiddles: once, "The tortoiseshell Tiddles is a rather affectionate cat."
    Tiddles: once, "Tiddles, no siamese, likes to miaow."

Element:
    !doctype: sixfold
    abbr: twice
      title: twice
    body: sixfold
    dd: sevenfold
    dfn: fivefold
      title: twice
    div: tenfold
      hidden: once
      id: fourfold
      itemid: once
      itemprop: thrice
      itemref: thrice
      itemscope: eightfold
      itemtype: fivefold
    dl: once
    dt: eightfold
    h1: sixfold
    head: sixfold
    html: sixfold
      lang: thrice
    link: fourfold
      href: fourfold
      itemprop: fourfold
    meta: 18fold
      content: 16fold
      http-equiv: twice
      itemprop: sevenfold
      itemref: twice
      itemscope: twice
      itemtype: twice
      name: ninefold
    p: 13fold
      class: thrice
      id: once
      lang: once
    span: fivefold
      id: once
      itemprop: fourfold
    title: sixfold
  Attribute count:
    class: thrice
    content: 16fold
    hidden: once
    href: fourfold
    http-equiv: twice
    id: sixfold
    itemid: once
    itemprop: 18fold
    itemref: fivefold
    itemscope: tenfold
    itemtype: sevenfold
    lang: fourfold
    name: ninefold
    title: fourfold
  20 elements used 295fold

Nits Reported:
    Errors: once
    Warnings: tenfold

File Info:
    4025 bytes read in 6 files, with an average of roughly 671 bytes per file
    smallest file: 252 bytes, largest file: 1019 bytes

Id:
  a declared never, used once
  amanda declared never, used once
  b declared never, used once
  c declared never, used once
  comments declared never, used once
  tid declared never, used once

Id/Element:
  div#amanda declared never, used once
  div#b declared never, used once
  div#c declared never, used once
  div#tid declared never, used once
  p#a declared never, used once
  span#comments declared never, used once

ItemId:
    a: never
    amanda: never
    b: never
    c: never
    comments: never
    tid: never
  6 ItemId used never

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
      publisher: once
    http://schema.org/Organization: thrice
      founder: twice
      name: twice
      url: twice
    http://schema.org/Person: twice
  Property counts:
    founder: twice
    name: twice
    publisher: once
    url: twice
  3 itemtypes used sevenfold

Reference:
    HTML 5.0: thrice
    WhatWG HTML 5, Jul 20: twice

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
    HTML-5/20210101/SVG-2.0/MathML-core/CSS-2.1/WhatWG: sixfold
===

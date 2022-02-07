#pragma once
#include "feedback/nitpick.h"
#include "utility/common.h"
#include "spell/spell.h"
#include "icu/lingo.h"

class phrase
{   lingo lang_;
    ::std::string text_;
public:
    void extend (const lingo& lang, const ::std::string& s)
    {   lang_ = lang;
        text_ += s; }
    void complete (nitpick& nits, const html_version& v)
    {   if (! text_.empty ())
        {   spell (nits, v, lang_, text_);
            text_.clear (); } } };


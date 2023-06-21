/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "main/standard.h"
#include "type/type.h"

struct symbol_entry < html_version, e_lang > lang_symbol_table [] =
{   { { HTML_4_0 }, { HTML_UNDEF },   "globlish", la_context },

    // https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes
    { { HTML_PLUS }, { HTML_UNDEF }, "aa", la_aa },
    { { HTML_PLUS }, { HTML_UNDEF }, "ab", la_ab },
    { { HTML_PLUS }, { HTML_UNDEF }, "ae", la_ae },
    { { HTML_PLUS }, { HTML_UNDEF }, "af", la_af },
    { { HTML_PLUS }, { HTML_UNDEF }, "ak", la_ak },
    { { HTML_PLUS }, { HTML_UNDEF }, "am", la_am },
    { { HTML_PLUS }, { HTML_UNDEF }, "an", la_an },
    { { HTML_PLUS }, { HTML_UNDEF }, "ar", la_ar },
    { { HTML_PLUS }, { HTML_UNDEF }, "as", la_as },
    { { HTML_PLUS }, { HTML_UNDEF }, "av", la_av },
    { { HTML_PLUS }, { HTML_UNDEF }, "ay", la_ay },
    { { HTML_PLUS }, { HTML_UNDEF }, "az", la_az },
    { { HTML_PLUS }, { HTML_UNDEF }, "ba", la_ba },
    { { HTML_PLUS }, { HTML_UNDEF }, "be", la_be },
    { { HTML_PLUS }, { HTML_UNDEF }, "bg", la_bg },
    { { HTML_PLUS }, { HTML_UNDEF }, "bh", la_bh },
    { { HTML_PLUS }, { HTML_UNDEF }, "bi", la_bi },
    { { HTML_PLUS }, { HTML_UNDEF }, "bm", la_bm },
    { { HTML_PLUS }, { HTML_UNDEF }, "bn", la_bn },
    { { HTML_PLUS }, { HTML_UNDEF }, "bo", la_bo },
    { { HTML_PLUS }, { HTML_UNDEF }, "br", la_br },
    { { HTML_PLUS }, { HTML_UNDEF }, "bs", la_bs },
    { { HTML_PLUS }, { HTML_UNDEF }, "ca", la_ca },
    { { HTML_PLUS }, { HTML_UNDEF }, "ce", la_ce },
    { { HTML_PLUS }, { HTML_UNDEF }, "ch", la_ch },
    { { HTML_PLUS }, { HTML_UNDEF }, "co", la_co },
    { { HTML_PLUS }, { HTML_UNDEF }, "cr", la_cr },
    { { HTML_PLUS }, { HTML_UNDEF }, "cs", la_cs },
    { { HTML_PLUS }, { HTML_UNDEF }, "cu", la_cu },
    { { HTML_PLUS }, { HTML_UNDEF }, "cv", la_cv },
    { { HTML_PLUS }, { HTML_UNDEF }, "cy", la_cy },
    { { HTML_PLUS }, { HTML_UNDEF }, "da", la_da },
    { { HTML_PLUS }, { HTML_UNDEF }, "de", la_de },
    { { HTML_PLUS }, { HTML_UNDEF }, "dv", la_dv },
    { { HTML_PLUS }, { HTML_UNDEF }, "dz", la_dz },
    { { HTML_PLUS }, { HTML_UNDEF }, "ee", la_ee },
    { { HTML_PLUS }, { HTML_UNDEF }, "el", la_el },
    { { HTML_PLUS }, { HTML_UNDEF }, "en", la_en },
    { { HTML_PLUS }, { HTML_UNDEF }, "eo", la_eo },
    { { HTML_PLUS }, { HTML_UNDEF }, "es", la_es },
    { { HTML_PLUS }, { HTML_UNDEF }, "et", la_et },
    { { HTML_PLUS }, { HTML_UNDEF }, "eu", la_eu },
    { { HTML_PLUS }, { HTML_UNDEF }, "fa", la_fa },
    { { HTML_PLUS }, { HTML_UNDEF }, "ff", la_ff },
    { { HTML_PLUS }, { HTML_UNDEF }, "fi", la_fi },
    { { HTML_PLUS }, { HTML_UNDEF }, "fj", la_fj },
    { { HTML_PLUS }, { HTML_UNDEF }, "fo", la_fo },
    { { HTML_PLUS }, { HTML_UNDEF }, "fr", la_fr },
    { { HTML_PLUS }, { HTML_UNDEF }, "fy", la_fy },
    { { HTML_PLUS }, { HTML_UNDEF }, "ga", la_ga },
    { { HTML_PLUS }, { HTML_UNDEF }, "gd", la_gd },
    { { HTML_PLUS }, { HTML_UNDEF }, "gl", la_gl },
    { { HTML_PLUS }, { HTML_UNDEF }, "gn", la_gn },
    { { HTML_PLUS }, { HTML_UNDEF }, "gu", la_gu },
    { { HTML_PLUS }, { HTML_UNDEF }, "gv", la_gv },
    { { HTML_PLUS }, { HTML_UNDEF }, "ha", la_ha },
    { { HTML_PLUS }, { HTML_UNDEF }, "he", la_he },
    { { HTML_PLUS }, { HTML_UNDEF }, "hi", la_hi },
    { { HTML_PLUS }, { HTML_UNDEF }, "ho", la_ho },
    { { HTML_PLUS }, { HTML_UNDEF }, "hr", la_hr },
    { { HTML_PLUS }, { HTML_UNDEF }, "ht", la_ht },
    { { HTML_PLUS }, { HTML_UNDEF }, "hu", la_hu },
    { { HTML_PLUS }, { HTML_UNDEF }, "hy", la_hy },
    { { HTML_PLUS }, { HTML_UNDEF }, "hz", la_hz },
    { { HTML_PLUS }, { HTML_UNDEF }, "ia", la_ia },
    { { HTML_PLUS }, { HTML_UNDEF }, "id", la_id },
    { { HTML_PLUS }, { HTML_UNDEF }, "ie", la_ie },
    { { HTML_PLUS }, { HTML_UNDEF }, "ig", la_ig },
    { { HTML_PLUS }, { HTML_UNDEF }, "ii", la_ii },
    { { HTML_PLUS }, { HTML_UNDEF }, "ik", la_ik },
    { { HTML_PLUS }, { HTML_UNDEF }, "io", la_io },
    { { HTML_PLUS }, { HTML_UNDEF }, "is", la_is },
    { { HTML_PLUS }, { HTML_UNDEF }, "it", la_it },
    { { HTML_PLUS }, { HTML_UNDEF }, "iu", la_iu },
    { { HTML_PLUS }, { HTML_UNDEF }, "ja", la_ja },
    { { HTML_PLUS }, { HTML_UNDEF }, "jv", la_jv },
    { { HTML_PLUS }, { HTML_UNDEF }, "ka", la_ka },
    { { HTML_PLUS }, { HTML_UNDEF }, "kg", la_kg },
    { { HTML_PLUS }, { HTML_UNDEF }, "ki", la_ki },
    { { HTML_PLUS }, { HTML_UNDEF }, "kj", la_kj },
    { { HTML_PLUS }, { HTML_UNDEF }, "kk", la_kk },
    { { HTML_PLUS }, { HTML_UNDEF }, "kl", la_kl },
    { { HTML_PLUS }, { HTML_UNDEF }, "km", la_km },
    { { HTML_PLUS }, { HTML_UNDEF }, "kn", la_kn },
    { { HTML_PLUS }, { HTML_UNDEF }, "ko", la_ko },
    { { HTML_PLUS }, { HTML_UNDEF }, "kr", la_kr },
    { { HTML_PLUS }, { HTML_UNDEF }, "ks", la_ks },
    { { HTML_PLUS }, { HTML_UNDEF }, "ku", la_ku },
    { { HTML_PLUS }, { HTML_UNDEF }, "kv", la_kv },
    { { HTML_PLUS }, { HTML_UNDEF }, "kw", la_kw },
    { { HTML_PLUS }, { HTML_UNDEF }, "ky", la_ky },
    { { HTML_PLUS }, { HTML_UNDEF }, "la", la_la },
    { { HTML_PLUS }, { HTML_UNDEF }, "lb", la_lb },
    { { HTML_PLUS }, { HTML_UNDEF }, "lg", la_lg },
    { { HTML_PLUS }, { HTML_UNDEF }, "li", la_li },
    { { HTML_PLUS }, { HTML_UNDEF }, "ln", la_ln },
    { { HTML_PLUS }, { HTML_UNDEF }, "lo", la_lo },
    { { HTML_PLUS }, { HTML_UNDEF }, "lt", la_lt },
    { { HTML_PLUS }, { HTML_UNDEF }, "lu", la_lu },
    { { HTML_PLUS }, { HTML_UNDEF }, "lv", la_lv },
    { { HTML_PLUS }, { HTML_UNDEF }, "mg", la_mg },
    { { HTML_PLUS }, { HTML_UNDEF }, "mh", la_mh },
    { { HTML_PLUS }, { HTML_UNDEF }, "mi", la_mi },
    { { HTML_PLUS }, { HTML_UNDEF }, "mk", la_mk },
    { { HTML_PLUS }, { HTML_UNDEF }, "ml", la_ml },
    { { HTML_PLUS }, { HTML_UNDEF }, "mn", la_mn },
    { { HTML_PLUS }, { HTML_UNDEF }, "mr", la_mr },
    { { HTML_PLUS }, { HTML_UNDEF }, "ms", la_ms },
    { { HTML_PLUS }, { HTML_UNDEF }, "mt", la_mt },
    { { HTML_PLUS }, { HTML_UNDEF }, "my", la_my },
    { { HTML_PLUS }, { HTML_UNDEF }, "na", la_na },
    { { HTML_PLUS }, { HTML_UNDEF }, "nb", la_nb },
    { { HTML_PLUS }, { HTML_UNDEF }, "nd", la_nd },
    { { HTML_PLUS }, { HTML_UNDEF }, "ne", la_ne },
    { { HTML_PLUS }, { HTML_UNDEF }, "ng", la_ng },
    { { HTML_PLUS }, { HTML_UNDEF }, "nl", la_nl },
    { { HTML_PLUS }, { HTML_UNDEF }, "nn", la_nn },
    { { HTML_PLUS }, { HTML_UNDEF }, "no", la_no },
    { { HTML_PLUS }, { HTML_UNDEF }, "nr", la_nr },
    { { HTML_PLUS }, { HTML_UNDEF }, "nv", la_nv },
    { { HTML_PLUS }, { HTML_UNDEF }, "ny", la_ny },
    { { HTML_PLUS }, { HTML_UNDEF }, "oc", la_oc },
    { { HTML_PLUS }, { HTML_UNDEF }, "oj", la_oj },
    { { HTML_PLUS }, { HTML_UNDEF }, "om", la_om },
    { { HTML_PLUS }, { HTML_UNDEF }, "or", la_or },
    { { HTML_PLUS }, { HTML_UNDEF }, "os", la_os },
    { { HTML_PLUS }, { HTML_UNDEF }, "pa", la_pa },
    { { HTML_PLUS }, { HTML_UNDEF }, "pi", la_pi },
    { { HTML_PLUS }, { HTML_UNDEF }, "pl", la_pl },
    { { HTML_PLUS }, { HTML_UNDEF }, "ps", la_ps },
    { { HTML_PLUS }, { HTML_UNDEF }, "pt", la_pt },
    { { HTML_PLUS }, { HTML_UNDEF }, "qu", la_qu },
    { { HTML_PLUS }, { HTML_UNDEF }, "rm", la_rm },
    { { HTML_PLUS }, { HTML_UNDEF }, "rn", la_rn },
    { { HTML_PLUS }, { HTML_UNDEF }, "ro", la_ro },
    { { HTML_PLUS }, { HTML_UNDEF }, "ru", la_ru },
    { { HTML_PLUS }, { HTML_UNDEF }, "rw", la_rw },
    { { HTML_PLUS }, { HTML_UNDEF }, "sa", la_sa },
    { { HTML_PLUS }, { HTML_UNDEF }, "sc", la_sc },
    { { HTML_PLUS }, { HTML_UNDEF }, "sd", la_sd },
    { { HTML_PLUS }, { HTML_UNDEF }, "se", la_se },
    { { HTML_PLUS }, { HTML_UNDEF }, "sg", la_sg },
    { { HTML_PLUS }, { HTML_UNDEF }, "si", la_si },
    { { HTML_PLUS }, { HTML_UNDEF }, "sk", la_sk },
    { { HTML_PLUS }, { HTML_UNDEF }, "sl", la_sl },
    { { HTML_PLUS }, { HTML_UNDEF }, "sm", la_sm },
    { { HTML_PLUS }, { HTML_UNDEF }, "sn", la_sn },
    { { HTML_PLUS }, { HTML_UNDEF }, "so", la_so },
    { { HTML_PLUS }, { HTML_UNDEF }, "sq", la_sq },
    { { HTML_PLUS }, { HTML_UNDEF }, "sr", la_sr },
    { { HTML_PLUS }, { HTML_UNDEF }, "ss", la_ss },
    { { HTML_PLUS }, { HTML_UNDEF }, "st", la_st },
    { { HTML_PLUS }, { HTML_UNDEF }, "su", la_su },
    { { HTML_PLUS }, { HTML_UNDEF }, "sv", la_sv },
    { { HTML_PLUS }, { HTML_UNDEF }, "sw", la_sw },
    { { HTML_PLUS }, { HTML_UNDEF }, "ta", la_ta },
    { { HTML_PLUS }, { HTML_UNDEF }, "te", la_te },
    { { HTML_PLUS }, { HTML_UNDEF }, "tg", la_tg },
    { { HTML_PLUS }, { HTML_UNDEF }, "th", la_th },
    { { HTML_PLUS }, { HTML_UNDEF }, "ti", la_ti },
    { { HTML_PLUS }, { HTML_UNDEF }, "tk", la_tk },
    { { HTML_PLUS }, { HTML_UNDEF }, "tl", la_tl },
    { { HTML_PLUS }, { HTML_UNDEF }, "tn", la_tn },
    { { HTML_PLUS }, { HTML_UNDEF }, "to", la_to },
    { { HTML_PLUS }, { HTML_UNDEF }, "tr", la_tr },
    { { HTML_PLUS }, { HTML_UNDEF }, "ts", la_ts },
    { { HTML_PLUS }, { HTML_UNDEF }, "tt", la_tt },
    { { HTML_PLUS }, { HTML_UNDEF }, "tw", la_tw },
    { { HTML_PLUS }, { HTML_UNDEF }, "ty", la_ty },
    { { HTML_PLUS }, { HTML_UNDEF }, "ug", la_ug },
    { { HTML_PLUS }, { HTML_UNDEF }, "uk", la_uk },
    { { HTML_PLUS }, { HTML_UNDEF }, "ur", la_ur },
    { { HTML_PLUS }, { HTML_UNDEF }, "uz", la_uz },
    { { HTML_PLUS }, { HTML_UNDEF }, "ve", la_ve },
    { { HTML_PLUS }, { HTML_UNDEF }, "vi", la_vi },
    { { HTML_PLUS }, { HTML_UNDEF }, "vo", la_vo },
    { { HTML_PLUS }, { HTML_UNDEF }, "wa", la_wa },
    { { HTML_PLUS }, { HTML_UNDEF }, "wo", la_wo },
    { { HTML_PLUS }, { HTML_UNDEF }, "xh", la_xh },
    { { HTML_PLUS }, { HTML_UNDEF }, "yi", la_yi },
    { { HTML_PLUS }, { HTML_UNDEF }, "yo", la_yo },
    { { HTML_PLUS }, { HTML_UNDEF }, "za", la_za },
    { { HTML_PLUS }, { HTML_UNDEF }, "zh", la_zh },
    { { HTML_PLUS }, { HTML_UNDEF }, "zu", la_zu },

    // https://en.wikipedia.org/wiki/List_of_ISO_639-2_codes
    // note qaa to qtz is "reserved for local use"
    { { HTML_4_0 }, { HTML_UNDEF }, "aar", la_aar },
    { { HTML_4_0 }, { HTML_UNDEF }, "abk", la_abk },
    { { HTML_4_0 }, { HTML_UNDEF }, "ace", la_ace },
    { { HTML_4_0 }, { HTML_UNDEF }, "ach", la_ach },
    { { HTML_4_0 }, { HTML_UNDEF }, "ada", la_ada },
    { { HTML_4_0 }, { HTML_UNDEF }, "ady", la_ady },
    { { HTML_4_0 }, { HTML_UNDEF }, "afa", la_afa },
    { { HTML_4_0 }, { HTML_UNDEF }, "afh", la_afh },
    { { HTML_4_0 }, { HTML_UNDEF }, "afr", la_afr },
    { { HTML_4_0 }, { HTML_UNDEF }, "ain", la_ain },
    { { HTML_4_0 }, { HTML_UNDEF }, "aka", la_aka },
    { { HTML_4_0 }, { HTML_UNDEF }, "akk", la_akk },
    { { HTML_4_0 }, { HTML_UNDEF }, "alb", la_alb },
    { { HTML_4_0 }, { HTML_UNDEF }, "ale", la_ale },
    { { HTML_4_0 }, { HTML_UNDEF }, "alg", la_alg },
    { { HTML_4_0 }, { HTML_UNDEF }, "alt", la_alt },
    { { HTML_4_0 }, { HTML_UNDEF }, "amh", la_amh },
    { { HTML_4_0 }, { HTML_UNDEF }, "ang", la_ang },
    { { HTML_4_0 }, { HTML_UNDEF }, "anp", la_anp },
    { { HTML_4_0 }, { HTML_UNDEF }, "apa", la_apa },
    { { HTML_4_0 }, { HTML_UNDEF }, "ara", la_ara },
    { { HTML_4_0 }, { HTML_UNDEF }, "arc", la_arc },
    { { HTML_4_0 }, { HTML_UNDEF }, "arg", la_arg },
    { { HTML_4_0 }, { HTML_UNDEF }, "arm", la_arm },
    { { HTML_4_0 }, { HTML_UNDEF }, "arn", la_arn },
    { { HTML_4_0 }, { HTML_UNDEF }, "arp", la_arp },
    { { HTML_4_0 }, { HTML_UNDEF }, "art", la_art },
    { { HTML_4_0 }, { HTML_UNDEF }, "arw", la_arw },
    { { HTML_4_0 }, { HTML_UNDEF }, "asm", la_asm },
    { { HTML_4_0 }, { HTML_UNDEF }, "ast", la_ast },
    { { HTML_4_0 }, { HTML_UNDEF }, "ath", la_ath },
    { { HTML_4_0 }, { HTML_UNDEF }, "aus", la_aus },
    { { HTML_4_0 }, { HTML_UNDEF }, "ava", la_ava },
    { { HTML_4_0 }, { HTML_UNDEF }, "ave", la_ave },
    { { HTML_4_0 }, { HTML_UNDEF }, "awa", la_awa },
    { { HTML_4_0 }, { HTML_UNDEF }, "aym", la_aym },
    { { HTML_4_0 }, { HTML_UNDEF }, "aze", la_aze },
    { { HTML_4_0 }, { HTML_UNDEF }, "bad", la_bad },
    { { HTML_4_0 }, { HTML_UNDEF }, "bai", la_bai },
    { { HTML_4_0 }, { HTML_UNDEF }, "bak", la_bak },
    { { HTML_4_0 }, { HTML_UNDEF }, "bal", la_bal },
    { { HTML_4_0 }, { HTML_UNDEF }, "bam", la_bam },
    { { HTML_4_0 }, { HTML_UNDEF }, "ban", la_ban },
    { { HTML_4_0 }, { HTML_UNDEF }, "baq", la_baq },
    { { HTML_4_0 }, { HTML_UNDEF }, "bas", la_bas },
    { { HTML_4_0 }, { HTML_UNDEF }, "bat", la_bat },
    { { HTML_4_0 }, { HTML_UNDEF }, "bej", la_bej },
    { { HTML_4_0 }, { HTML_UNDEF }, "bel", la_bel },
    { { HTML_4_0 }, { HTML_UNDEF }, "bem", la_bem },
    { { HTML_4_0 }, { HTML_UNDEF }, "ben", la_ben },
    { { HTML_4_0 }, { HTML_UNDEF }, "ber", la_ber },
    { { HTML_4_0 }, { HTML_UNDEF }, "bho", la_bho },
    { { HTML_4_0 }, { HTML_UNDEF }, "bih", la_bih },
    { { HTML_4_0 }, { HTML_UNDEF }, "bik", la_bik },
    { { HTML_4_0 }, { HTML_UNDEF }, "bin", la_bin },
    { { HTML_4_0 }, { HTML_UNDEF }, "bis", la_bis },
    { { HTML_4_0 }, { HTML_UNDEF }, "bla", la_bla },
    { { HTML_4_0 }, { HTML_UNDEF }, "bnt", la_bnt },
    { { HTML_4_0 }, { HTML_UNDEF }, "bod", la_bod },
    { { HTML_4_0 }, { HTML_UNDEF }, "bos", la_bos },
    { { HTML_4_0 }, { HTML_UNDEF }, "bra", la_bra },
    { { HTML_4_0 }, { HTML_UNDEF }, "bre", la_bre },
    { { HTML_4_0 }, { HTML_UNDEF }, "btk", la_btk },
    { { HTML_4_0 }, { HTML_UNDEF }, "bua", la_bua },
    { { HTML_4_0 }, { HTML_UNDEF }, "bug", la_bug },
    { { HTML_4_0 }, { HTML_UNDEF }, "bul", la_bul },
    { { HTML_4_0 }, { HTML_UNDEF }, "bur", la_bur },
    { { HTML_4_0 }, { HTML_UNDEF }, "byn", la_byn },
    { { HTML_4_0 }, { HTML_UNDEF }, "cad", la_cad },
    { { HTML_4_0 }, { HTML_UNDEF }, "cai", la_cai },
    { { HTML_4_0 }, { HTML_UNDEF }, "car", la_car },
    { { HTML_4_0 }, { HTML_UNDEF }, "cat", la_cat },
    { { HTML_4_0 }, { HTML_UNDEF }, "cau", la_cau },
    { { HTML_4_0 }, { HTML_UNDEF }, "ceb", la_ceb },
    { { HTML_4_0 }, { HTML_UNDEF }, "cel", la_cel },
    { { HTML_4_0 }, { HTML_UNDEF }, "ces", la_ces },
    { { HTML_4_0 }, { HTML_UNDEF }, "cha", la_cha },
    { { HTML_4_0 }, { HTML_UNDEF }, "chb", la_chb },
    { { HTML_4_0 }, { HTML_UNDEF }, "che", la_che },
    { { HTML_4_0 }, { HTML_UNDEF }, "chg", la_chg },
    { { HTML_4_0 }, { HTML_UNDEF }, "chi", la_chi },
    { { HTML_4_0 }, { HTML_UNDEF }, "chk", la_chk },
    { { HTML_4_0 }, { HTML_UNDEF }, "chm", la_chm },
    { { HTML_4_0 }, { HTML_UNDEF }, "chn", la_chn },
    { { HTML_4_0 }, { HTML_UNDEF }, "cho", la_cho },
    { { HTML_4_0 }, { HTML_UNDEF }, "chp", la_chp },
    { { HTML_4_0 }, { HTML_UNDEF }, "chr", la_chr },
    { { HTML_4_0 }, { HTML_UNDEF }, "chu", la_chu },
    { { HTML_4_0 }, { HTML_UNDEF }, "chv", la_chv },
    { { HTML_4_0 }, { HTML_UNDEF }, "chy", la_chy },
    { { HTML_4_0 }, { HTML_UNDEF }, "cmc", la_cmc },
    { { HTML_4_0 }, { HTML_UNDEF }, "cnr", la_cnr },
    { { HTML_4_0 }, { HTML_UNDEF }, "cop", la_cop },
    { { HTML_4_0 }, { HTML_UNDEF }, "cor", la_cor },
    { { HTML_4_0 }, { HTML_UNDEF }, "cos", la_cos },
    { { HTML_4_0 }, { HTML_UNDEF }, "cpe", la_cpe },
    { { HTML_4_0 }, { HTML_UNDEF }, "cpf", la_cpf },
    { { HTML_4_0 }, { HTML_UNDEF }, "cpp", la_cpp },
    { { HTML_4_0 }, { HTML_UNDEF }, "cre", la_cre },
    { { HTML_4_0 }, { HTML_UNDEF }, "crh", la_crh },
    { { HTML_4_0 }, { HTML_UNDEF }, "crp", la_crp },
    { { HTML_4_0 }, { HTML_UNDEF }, "csb", la_csb },
    { { HTML_4_0 }, { HTML_UNDEF }, "cus", la_cus },
    { { HTML_4_0 }, { HTML_UNDEF }, "cym", la_cym },
    { { HTML_4_0 }, { HTML_UNDEF }, "cze", la_cze },
    { { HTML_4_0 }, { HTML_UNDEF }, "dak", la_dak },
    { { HTML_4_0 }, { HTML_UNDEF }, "dan", la_dan },
    { { HTML_4_0 }, { HTML_UNDEF }, "dar", la_dar },
    { { HTML_4_0 }, { HTML_UNDEF }, "day", la_day },
    { { HTML_4_0 }, { HTML_UNDEF }, "del", la_del },
    { { HTML_4_0 }, { HTML_UNDEF }, "den", la_den },
    { { HTML_4_0 }, { HTML_UNDEF }, "deu", la_deu },
    { { HTML_4_0 }, { HTML_UNDEF }, "dgr", la_dgr },
    { { HTML_4_0 }, { HTML_UNDEF }, "din", la_din },
    { { HTML_4_0 }, { HTML_UNDEF }, "div", la_div },
    { { HTML_4_0 }, { HTML_UNDEF }, "doi", la_doi },
    { { HTML_4_0 }, { HTML_UNDEF }, "dra", la_dra },
    { { HTML_4_0 }, { HTML_UNDEF }, "dsb", la_dsb },
    { { HTML_4_0 }, { HTML_UNDEF }, "dua", la_dua },
    { { HTML_4_0 }, { HTML_UNDEF }, "dum", la_dum },
    { { HTML_4_0 }, { HTML_UNDEF }, "dut", la_dut },
    { { HTML_4_0 }, { HTML_UNDEF }, "dyu", la_dyu },
    { { HTML_4_0 }, { HTML_UNDEF }, "dzo", la_dzo },
    { { HTML_4_0 }, { HTML_UNDEF }, "efi", la_efi },
    { { HTML_4_0 }, { HTML_UNDEF }, "egy", la_egy },
    { { HTML_4_0 }, { HTML_UNDEF }, "eka", la_eka },
    { { HTML_4_0 }, { HTML_UNDEF }, "ell", la_ell },
    { { HTML_4_0 }, { HTML_UNDEF }, "elx", la_elx },
    { { HTML_4_0 }, { HTML_UNDEF }, "eng", la_eng },
    { { HTML_4_0 }, { HTML_UNDEF }, "enm", la_enm },
    { { HTML_4_0 }, { HTML_UNDEF }, "epo", la_epo },
    { { HTML_4_0 }, { HTML_UNDEF }, "est", la_est },
    { { HTML_4_0 }, { HTML_UNDEF }, "eus", la_eus },
    { { HTML_4_0 }, { HTML_UNDEF }, "ewe", la_ewe },
    { { HTML_4_0 }, { HTML_UNDEF }, "ewo", la_ewo },
    { { HTML_4_0 }, { HTML_UNDEF }, "fan", la_fan },
    { { HTML_4_0 }, { HTML_UNDEF }, "fao", la_fao },
    { { HTML_4_0 }, { HTML_UNDEF }, "fas", la_fas },
    { { HTML_4_0 }, { HTML_UNDEF }, "fat", la_fat },
    { { HTML_4_0 }, { HTML_UNDEF }, "fij", la_fij },
    { { HTML_4_0 }, { HTML_UNDEF }, "fil", la_fil },
    { { HTML_4_0 }, { HTML_UNDEF }, "fin", la_fin },
    { { HTML_4_0 }, { HTML_UNDEF }, "fiu", la_fiu },
    { { HTML_4_0 }, { HTML_UNDEF }, "fon", la_fon },
    { { HTML_4_0 }, { HTML_UNDEF }, "fra", la_fra },
    { { HTML_4_0 }, { HTML_UNDEF }, "fre", la_fre },
    { { HTML_4_0 }, { HTML_UNDEF }, "frm", la_frm },
    { { HTML_4_0 }, { HTML_UNDEF }, "fro", la_fro },
    { { HTML_4_0 }, { HTML_UNDEF }, "frr", la_frr },
    { { HTML_4_0 }, { HTML_UNDEF }, "frs", la_frs },
    { { HTML_4_0 }, { HTML_UNDEF }, "fry", la_fry },
    { { HTML_4_0 }, { HTML_UNDEF }, "ful", la_ful },
    { { HTML_4_0 }, { HTML_UNDEF }, "fur", la_fur },
    { { HTML_4_0 }, { HTML_UNDEF }, "gaa", la_gaa },
    { { HTML_4_0 }, { HTML_UNDEF }, "gay", la_gay },
    { { HTML_4_0 }, { HTML_UNDEF }, "gba", la_gba },
    { { HTML_4_0 }, { HTML_UNDEF }, "gem", la_gem },
    { { HTML_4_0 }, { HTML_UNDEF }, "geo", la_geo },
    { { HTML_4_0 }, { HTML_UNDEF }, "ger", la_ger },
    { { HTML_4_0 }, { HTML_UNDEF }, "gez", la_gez },
    { { HTML_4_0 }, { HTML_UNDEF }, "gil", la_gil },
    { { HTML_4_0 }, { HTML_UNDEF }, "gla", la_gla },
    { { HTML_4_0 }, { HTML_UNDEF }, "gle", la_gle },
    { { HTML_4_0 }, { HTML_UNDEF }, "glg", la_glg },
    { { HTML_4_0 }, { HTML_UNDEF }, "glv", la_glv },
    { { HTML_4_0 }, { HTML_UNDEF }, "gmh", la_gmh },
    { { HTML_4_0 }, { HTML_UNDEF }, "goh", la_goh },
    { { HTML_4_0 }, { HTML_UNDEF }, "gon", la_gon },
    { { HTML_4_0 }, { HTML_UNDEF }, "gor", la_gor },
    { { HTML_4_0 }, { HTML_UNDEF }, "got", la_got },
    { { HTML_4_0 }, { HTML_UNDEF }, "grb", la_grb },
    { { HTML_4_0 }, { HTML_UNDEF }, "grc", la_grc },
    { { HTML_4_0 }, { HTML_UNDEF }, "gre", la_gre },
    { { HTML_4_0 }, { HTML_UNDEF }, "grn", la_grn },
    { { HTML_4_0 }, { HTML_UNDEF }, "gsw", la_gsw },
    { { HTML_4_0 }, { HTML_UNDEF }, "guj", la_guj },
    { { HTML_4_0 }, { HTML_UNDEF }, "gwi", la_gwi },
    { { HTML_4_0 }, { HTML_UNDEF }, "hai", la_hai },
    { { HTML_4_0 }, { HTML_UNDEF }, "hat", la_hat },
    { { HTML_4_0 }, { HTML_UNDEF }, "hau", la_hau },
    { { HTML_4_0 }, { HTML_UNDEF }, "haw", la_haw },
    { { HTML_4_0 }, { HTML_UNDEF }, "heb", la_heb },
    { { HTML_4_0 }, { HTML_UNDEF }, "her", la_her },
    { { HTML_4_0 }, { HTML_UNDEF }, "hil", la_hil },
    { { HTML_4_0 }, { HTML_UNDEF }, "him", la_him },
    { { HTML_4_0 }, { HTML_UNDEF }, "hin", la_hin },
    { { HTML_4_0 }, { HTML_UNDEF }, "hit", la_hit },
    { { HTML_4_0 }, { HTML_UNDEF }, "hmn", la_hmn },
    { { HTML_4_0 }, { HTML_UNDEF }, "hmo", la_hmo },
    { { HTML_4_0 }, { HTML_UNDEF }, "hrv", la_hrv },
    { { HTML_4_0 }, { HTML_UNDEF }, "hsb", la_hsb },
    { { HTML_4_0 }, { HTML_UNDEF }, "hun", la_hun },
    { { HTML_4_0 }, { HTML_UNDEF }, "hup", la_hup },
    { { HTML_4_0 }, { HTML_UNDEF }, "hye", la_hye },
    { { HTML_4_0 }, { HTML_UNDEF }, "iba", la_iba },
    { { HTML_4_0 }, { HTML_UNDEF }, "ibo", la_ibo },
    { { HTML_4_0 }, { HTML_UNDEF }, "ice", la_ice },
    { { HTML_4_0 }, { HTML_UNDEF }, "ido", la_ido },
    { { HTML_4_0 }, { HTML_UNDEF }, "iii", la_iii },
    { { HTML_4_0 }, { HTML_UNDEF }, "ijo", la_ijo },
    { { HTML_4_0 }, { HTML_UNDEF }, "iku", la_iku },
    { { HTML_4_0 }, { HTML_UNDEF }, "ile", la_ile },
    { { HTML_4_0 }, { HTML_UNDEF }, "ilo", la_ilo },
    { { HTML_4_0 }, { HTML_UNDEF }, "ina", la_ina },
    { { HTML_4_0 }, { HTML_UNDEF }, "inc", la_inc },
    { { HTML_4_0 }, { HTML_UNDEF }, "ind", la_ind },
    { { HTML_4_0 }, { HTML_UNDEF }, "ine", la_ine },
    { { HTML_4_0 }, { HTML_UNDEF }, "inh", la_inh },
    { { HTML_4_0 }, { HTML_UNDEF }, "ipk", la_ipk },
    { { HTML_4_0 }, { HTML_UNDEF }, "ira", la_ira },
    { { HTML_4_0 }, { HTML_UNDEF }, "iro", la_iro },
    { { HTML_4_0 }, { HTML_UNDEF }, "isl", la_isl },
    { { HTML_4_0 }, { HTML_UNDEF }, "ita", la_ita },
    { { HTML_4_0 }, { HTML_UNDEF }, "jav", la_jav },
    { { HTML_4_0 }, { HTML_UNDEF }, "jbo", la_jbo },
    { { HTML_4_0 }, { HTML_UNDEF }, "jpn", la_jpn },
    { { HTML_4_0 }, { HTML_UNDEF }, "jpr", la_jpr },
    { { HTML_4_0 }, { HTML_UNDEF }, "jrb", la_jrb },
    { { HTML_4_0 }, { HTML_UNDEF }, "kaa", la_kaa },
    { { HTML_4_0 }, { HTML_UNDEF }, "kab", la_kab },
    { { HTML_4_0 }, { HTML_UNDEF }, "kac", la_kac },
    { { HTML_4_0 }, { HTML_UNDEF }, "kal", la_kal },
    { { HTML_4_0 }, { HTML_UNDEF }, "kam", la_kam },
    { { HTML_4_0 }, { HTML_UNDEF }, "kan", la_kan },
    { { HTML_4_0 }, { HTML_UNDEF }, "kar", la_kar },
    { { HTML_4_0 }, { HTML_UNDEF }, "kas", la_kas },
    { { HTML_4_0 }, { HTML_UNDEF }, "kat", la_kat },
    { { HTML_4_0 }, { HTML_UNDEF }, "kau", la_kau },
    { { HTML_4_0 }, { HTML_UNDEF }, "kaw", la_kaw },
    { { HTML_4_0 }, { HTML_UNDEF }, "kaz", la_kaz },
    { { HTML_4_0 }, { HTML_UNDEF }, "kbd", la_kbd },
    { { HTML_4_0 }, { HTML_UNDEF }, "kha", la_kha },
    { { HTML_4_0 }, { HTML_UNDEF }, "khi", la_khi },
    { { HTML_4_0 }, { HTML_UNDEF }, "khm", la_khm },
    { { HTML_4_0 }, { HTML_UNDEF }, "kho", la_kho },
    { { HTML_4_0 }, { HTML_UNDEF }, "kik", la_kik },
    { { HTML_4_0 }, { HTML_UNDEF }, "kin", la_kin },
    { { HTML_4_0 }, { HTML_UNDEF }, "kir", la_kir },
    { { HTML_4_0 }, { HTML_UNDEF }, "kmb", la_kmb },
    { { HTML_4_0 }, { HTML_UNDEF }, "kok", la_kok },
    { { HTML_4_0 }, { HTML_UNDEF }, "kom", la_kom },
    { { HTML_4_0 }, { HTML_UNDEF }, "kon", la_kon },
    { { HTML_4_0 }, { HTML_UNDEF }, "kor", la_kor },
    { { HTML_4_0 }, { HTML_UNDEF }, "kos", la_kos },
    { { HTML_4_0 }, { HTML_UNDEF }, "kpe", la_kpe },
    { { HTML_4_0 }, { HTML_UNDEF }, "krc", la_krc },
    { { HTML_4_0 }, { HTML_UNDEF }, "krl", la_krl },
    { { HTML_4_0 }, { HTML_UNDEF }, "kro", la_kro },
    { { HTML_4_0 }, { HTML_UNDEF }, "kru", la_kru },
    { { HTML_4_0 }, { HTML_UNDEF }, "kua", la_kua },
    { { HTML_4_0 }, { HTML_UNDEF }, "kum", la_kum },
    { { HTML_4_0 }, { HTML_UNDEF }, "kur", la_kur },
    { { HTML_4_0 }, { HTML_UNDEF }, "kut", la_kut },
    { { HTML_4_0 }, { HTML_UNDEF }, "lad", la_lad },
    { { HTML_4_0 }, { HTML_UNDEF }, "lah", la_lah },
    { { HTML_4_0 }, { HTML_UNDEF }, "lam", la_lam },
    { { HTML_4_0 }, { HTML_UNDEF }, "lao", la_lao },
    { { HTML_4_0 }, { HTML_UNDEF }, "lat", la_lat },
    { { HTML_4_0 }, { HTML_UNDEF }, "lav", la_lav },
    { { HTML_4_0 }, { HTML_UNDEF }, "lez", la_lez },
    { { HTML_4_0 }, { HTML_UNDEF }, "lim", la_lim },
    { { HTML_4_0 }, { HTML_UNDEF }, "lin", la_lin },
    { { HTML_4_0 }, { HTML_UNDEF }, "lit", la_lit },
    { { HTML_4_0 }, { HTML_UNDEF }, "lol", la_lol },
    { { HTML_4_0 }, { HTML_UNDEF }, "loz", la_loz },
    { { HTML_4_0 }, { HTML_UNDEF }, "ltz", la_ltz },
    { { HTML_4_0 }, { HTML_UNDEF }, "lua", la_lua },
    { { HTML_4_0 }, { HTML_UNDEF }, "lub", la_lub },
    { { HTML_4_0 }, { HTML_UNDEF }, "lug", la_lug },
    { { HTML_4_0 }, { HTML_UNDEF }, "lui", la_lui },
    { { HTML_4_0 }, { HTML_UNDEF }, "lun", la_lun },
    { { HTML_4_0 }, { HTML_UNDEF }, "luo", la_luo },
    { { HTML_4_0 }, { HTML_UNDEF }, "lus", la_lus },
    { { HTML_4_0 }, { HTML_UNDEF }, "mac", la_mac },
    { { HTML_4_0 }, { HTML_UNDEF }, "mad", la_mad },
    { { HTML_4_0 }, { HTML_UNDEF }, "mag", la_mag },
    { { HTML_4_0 }, { HTML_UNDEF }, "mah", la_mah },
    { { HTML_4_0 }, { HTML_UNDEF }, "mai", la_mai },
    { { HTML_4_0 }, { HTML_UNDEF }, "mak", la_mak },
    { { HTML_4_0 }, { HTML_UNDEF }, "mal", la_mal },
    { { HTML_4_0 }, { HTML_UNDEF }, "man", la_man },
    { { HTML_4_0 }, { HTML_UNDEF }, "mao", la_mao },
    { { HTML_4_0 }, { HTML_UNDEF }, "map", la_map },
    { { HTML_4_0 }, { HTML_UNDEF }, "mar", la_mar },
    { { HTML_4_0 }, { HTML_UNDEF }, "mas", la_mas },
    { { HTML_4_0 }, { HTML_UNDEF }, "may", la_may },
    { { HTML_4_0 }, { HTML_UNDEF }, "mdf", la_mdf },
    { { HTML_4_0 }, { HTML_UNDEF }, "mdr", la_mdr },
    { { HTML_4_0 }, { HTML_UNDEF }, "men", la_men },
    { { HTML_4_0 }, { HTML_UNDEF }, "mga", la_mga },
    { { HTML_4_0 }, { HTML_UNDEF }, "mic", la_mic },
    { { HTML_4_0 }, { HTML_UNDEF }, "min", la_min },
    { { HTML_4_0 }, { HTML_UNDEF }, "mis", la_mis },
    { { HTML_4_0 }, { HTML_UNDEF }, "mkd", la_mkd },
    { { HTML_4_0 }, { HTML_UNDEF }, "mkh", la_mkh },
    { { HTML_4_0 }, { HTML_UNDEF }, "mlg", la_mlg },
    { { HTML_4_0 }, { HTML_UNDEF }, "mlt", la_mlt },
    { { HTML_4_0 }, { HTML_UNDEF }, "mnc", la_mnc },
    { { HTML_4_0 }, { HTML_UNDEF }, "mni", la_mni },
    { { HTML_4_0 }, { HTML_UNDEF }, "mno", la_mno },
    { { HTML_4_0 }, { HTML_UNDEF }, "moh", la_moh },
    { { HTML_4_0 }, { HTML_UNDEF }, "mon", la_mon },
    { { HTML_4_0 }, { HTML_UNDEF }, "mos", la_mos },
    { { HTML_4_0 }, { HTML_UNDEF }, "mri", la_mri },
    { { HTML_4_0 }, { HTML_UNDEF }, "msa", la_msa },
    { { HTML_4_0 }, { HTML_UNDEF }, "mul", la_mul },
    { { HTML_4_0 }, { HTML_UNDEF }, "mun", la_mun },
    { { HTML_4_0 }, { HTML_UNDEF }, "mus", la_mus },
    { { HTML_4_0 }, { HTML_UNDEF }, "mwl", la_mwl },
    { { HTML_4_0 }, { HTML_UNDEF }, "mwr", la_mwr },
    { { HTML_4_0 }, { HTML_UNDEF }, "mya", la_mya },
    { { HTML_4_0 }, { HTML_UNDEF }, "myn", la_myn },
    { { HTML_4_0 }, { HTML_UNDEF }, "myv", la_myv },
    { { HTML_4_0 }, { HTML_UNDEF }, "nah", la_nah },
    { { HTML_4_0 }, { HTML_UNDEF }, "nai", la_nai },
    { { HTML_4_0 }, { HTML_UNDEF }, "nap", la_nap },
    { { HTML_4_0 }, { HTML_UNDEF }, "nau", la_nau },
    { { HTML_4_0 }, { HTML_UNDEF }, "nav", la_nav },
    { { HTML_4_0 }, { HTML_UNDEF }, "nbl", la_nbl },
    { { HTML_4_0 }, { HTML_UNDEF }, "nde", la_nde },
    { { HTML_4_0 }, { HTML_UNDEF }, "ndo", la_ndo },
    { { HTML_4_0 }, { HTML_UNDEF }, "nds", la_nds },
    { { HTML_4_0 }, { HTML_UNDEF }, "nep", la_nep },
    { { HTML_4_0 }, { HTML_UNDEF }, "new", la_new },
    { { HTML_4_0 }, { HTML_UNDEF }, "nia", la_nia },
    { { HTML_4_0 }, { HTML_UNDEF }, "nic", la_nic },
    { { HTML_4_0 }, { HTML_UNDEF }, "niu", la_niu },
    { { HTML_4_0 }, { HTML_UNDEF }, "nld", la_nld },
    { { HTML_4_0 }, { HTML_UNDEF }, "nno", la_nno },
    { { HTML_4_0 }, { HTML_UNDEF }, "nob", la_nob },
    { { HTML_4_0 }, { HTML_UNDEF }, "nog", la_nog },
    { { HTML_4_0 }, { HTML_UNDEF }, "non", la_non },
    { { HTML_4_0 }, { HTML_UNDEF }, "nor", la_nor },
    { { HTML_4_0 }, { HTML_UNDEF }, "nqo", la_nqo },
    { { HTML_4_0 }, { HTML_UNDEF }, "nso", la_nso },
    { { HTML_4_0 }, { HTML_UNDEF }, "nub", la_nub },
    { { HTML_4_0 }, { HTML_UNDEF }, "nwc", la_nwc },
    { { HTML_4_0 }, { HTML_UNDEF }, "nya", la_nya },
    { { HTML_4_0 }, { HTML_UNDEF }, "nym", la_nym },
    { { HTML_4_0 }, { HTML_UNDEF }, "nyn", la_nyn },
    { { HTML_4_0 }, { HTML_UNDEF }, "nyo", la_nyo },
    { { HTML_4_0 }, { HTML_UNDEF }, "nzi", la_nzi },
    { { HTML_4_0 }, { HTML_UNDEF }, "oci", la_oci },
    { { HTML_4_0 }, { HTML_UNDEF }, "oji", la_oji },
    { { HTML_4_0 }, { HTML_UNDEF }, "ori", la_ori },
    { { HTML_4_0 }, { HTML_UNDEF }, "orm", la_orm },
    { { HTML_4_0 }, { HTML_UNDEF }, "osa", la_osa },
    { { HTML_4_0 }, { HTML_UNDEF }, "oss", la_oss },
    { { HTML_4_0 }, { HTML_UNDEF }, "ota", la_ota },
    { { HTML_4_0 }, { HTML_UNDEF }, "oto", la_oto },
    { { HTML_4_0 }, { HTML_UNDEF }, "paa", la_paa },
    { { HTML_4_0 }, { HTML_UNDEF }, "pag", la_pag },
    { { HTML_4_0 }, { HTML_UNDEF }, "pal", la_pal },
    { { HTML_4_0 }, { HTML_UNDEF }, "pam", la_pam },
    { { HTML_4_0 }, { HTML_UNDEF }, "pan", la_pan },
    { { HTML_4_0 }, { HTML_UNDEF }, "pap", la_pap },
    { { HTML_4_0 }, { HTML_UNDEF }, "pau", la_pau },
    { { HTML_4_0 }, { HTML_UNDEF }, "peo", la_peo },
    { { HTML_4_0 }, { HTML_UNDEF }, "per", la_per },
    { { HTML_4_0 }, { HTML_UNDEF }, "phi", la_phi },
    { { HTML_4_0 }, { HTML_UNDEF }, "phn", la_phn },
    { { HTML_4_0 }, { HTML_UNDEF }, "pli", la_pli },
    { { HTML_4_0 }, { HTML_UNDEF }, "pol", la_pol },
    { { HTML_4_0 }, { HTML_UNDEF }, "pon", la_pon },
    { { HTML_4_0 }, { HTML_UNDEF }, "por", la_por },
    { { HTML_4_0 }, { HTML_UNDEF }, "pra", la_pra },
    { { HTML_4_0 }, { HTML_UNDEF }, "pro", la_pro },
    { { HTML_4_0 }, { HTML_UNDEF }, "pus", la_pus },
    { { HTML_4_0 }, { HTML_UNDEF }, "que", la_que },
    { { HTML_4_0 }, { HTML_UNDEF }, "raj", la_raj },
    { { HTML_4_0 }, { HTML_UNDEF }, "rap", la_rap },
    { { HTML_4_0 }, { HTML_UNDEF }, "rar", la_rar },
    { { HTML_4_0 }, { HTML_UNDEF }, "roa", la_roa },
    { { HTML_4_0 }, { HTML_UNDEF }, "roh", la_roh },
    { { HTML_4_0 }, { HTML_UNDEF }, "rom", la_rom },
    { { HTML_4_0 }, { HTML_UNDEF }, "ron", la_ron },
    { { HTML_4_0 }, { HTML_UNDEF }, "rum", la_rum },
    { { HTML_4_0 }, { HTML_UNDEF }, "run", la_run },
    { { HTML_4_0 }, { HTML_UNDEF }, "rup", la_rup },
    { { HTML_4_0 }, { HTML_UNDEF }, "rus", la_rus },
    { { HTML_4_0 }, { HTML_UNDEF }, "sad", la_sad },
    { { HTML_4_0 }, { HTML_UNDEF }, "sag", la_sag },
    { { HTML_4_0 }, { HTML_UNDEF }, "sah", la_sah },
    { { HTML_4_0 }, { HTML_UNDEF }, "sai", la_sai },
    { { HTML_4_0 }, { HTML_UNDEF }, "sal", la_sal },
    { { HTML_4_0 }, { HTML_UNDEF }, "sam", la_sam },
    { { HTML_4_0 }, { HTML_UNDEF }, "san", la_san },
    { { HTML_4_0 }, { HTML_UNDEF }, "sas", la_sas },
    { { HTML_4_0 }, { HTML_UNDEF }, "sat", la_sat },
    { { HTML_4_0 }, { HTML_UNDEF }, "scn", la_scn },
    { { HTML_4_0 }, { HTML_UNDEF }, "sco", la_sco },
    { { HTML_4_0 }, { HTML_UNDEF }, "sel", la_sel },
    { { HTML_4_0 }, { HTML_UNDEF }, "sem", la_sem },
    { { HTML_4_0 }, { HTML_UNDEF }, "sga", la_sga },
    { { HTML_4_0 }, { HTML_UNDEF }, "sgn", la_sgn },
    { { HTML_4_0 }, { HTML_UNDEF }, "shn", la_shn },
    { { HTML_4_0 }, { HTML_UNDEF }, "sid", la_sid },
    { { HTML_4_0 }, { HTML_UNDEF }, "sin", la_sin },
    { { HTML_4_0 }, { HTML_UNDEF }, "sio", la_sio },
    { { HTML_4_0 }, { HTML_UNDEF }, "sit", la_sit },
    { { HTML_4_0 }, { HTML_UNDEF }, "sla", la_sla },
    { { HTML_4_0 }, { HTML_UNDEF }, "slk", la_slk },
    { { HTML_4_0 }, { HTML_UNDEF }, "slo", la_slo },
    { { HTML_4_0 }, { HTML_UNDEF }, "slv", la_slv },
    { { HTML_4_0 }, { HTML_UNDEF }, "sma", la_sma },
    { { HTML_4_0 }, { HTML_UNDEF }, "sme", la_sme },
    { { HTML_4_0 }, { HTML_UNDEF }, "smi", la_smi },
    { { HTML_4_0 }, { HTML_UNDEF }, "smj", la_smj },
    { { HTML_4_0 }, { HTML_UNDEF }, "smn", la_smn },
    { { HTML_4_0 }, { HTML_UNDEF }, "smo", la_smo },
    { { HTML_4_0 }, { HTML_UNDEF }, "sms", la_sms },
    { { HTML_4_0 }, { HTML_UNDEF }, "sna", la_sna },
    { { HTML_4_0 }, { HTML_UNDEF }, "snd", la_snd },
    { { HTML_4_0 }, { HTML_UNDEF }, "snk", la_snk },
    { { HTML_4_0 }, { HTML_UNDEF }, "sog", la_sog },
    { { HTML_4_0 }, { HTML_UNDEF }, "som", la_som },
    { { HTML_4_0 }, { HTML_UNDEF }, "son", la_son },
    { { HTML_4_0 }, { HTML_UNDEF }, "sot", la_sot },
    { { HTML_4_0 }, { HTML_UNDEF }, "spa", la_spa },
    { { HTML_4_0 }, { HTML_UNDEF }, "sqi", la_sqi },
    { { HTML_4_0 }, { HTML_UNDEF }, "srd", la_srd },
    { { HTML_4_0 }, { HTML_UNDEF }, "srn", la_srn },
    { { HTML_4_0 }, { HTML_UNDEF }, "srp", la_srp },
    { { HTML_4_0 }, { HTML_UNDEF }, "srr", la_srr },
    { { HTML_4_0 }, { HTML_UNDEF }, "ssa", la_ssa },
    { { HTML_4_0 }, { HTML_UNDEF }, "ssw", la_ssw },
    { { HTML_4_0 }, { HTML_UNDEF }, "suk", la_suk },
    { { HTML_4_0 }, { HTML_UNDEF }, "sun", la_sun },
    { { HTML_4_0 }, { HTML_UNDEF }, "sus", la_sus },
    { { HTML_4_0 }, { HTML_UNDEF }, "sux", la_sux },
    { { HTML_4_0 }, { HTML_UNDEF }, "swa", la_swa },
    { { HTML_4_0 }, { HTML_UNDEF }, "swe", la_swe },
    { { HTML_4_0 }, { HTML_UNDEF }, "syc", la_syc },
    { { HTML_4_0 }, { HTML_UNDEF }, "syr", la_syr },
    { { HTML_4_0 }, { HTML_UNDEF }, "tah", la_tah },
    { { HTML_4_0 }, { HTML_UNDEF }, "tai", la_tai },
    { { HTML_4_0 }, { HTML_UNDEF }, "tam", la_tam },
    { { HTML_4_0 }, { HTML_UNDEF }, "tat", la_tat },
    { { HTML_4_0 }, { HTML_UNDEF }, "tel", la_tel },
    { { HTML_4_0 }, { HTML_UNDEF }, "tem", la_tem },
    { { HTML_4_0 }, { HTML_UNDEF }, "ter", la_ter },
    { { HTML_4_0 }, { HTML_UNDEF }, "tet", la_tet },
    { { HTML_4_0 }, { HTML_UNDEF }, "tgk", la_tgk },
    { { HTML_4_0 }, { HTML_UNDEF }, "tgl", la_tgl },
    { { HTML_4_0 }, { HTML_UNDEF }, "tha", la_tha },
    { { HTML_4_0 }, { HTML_UNDEF }, "tib", la_tib },
    { { HTML_4_0 }, { HTML_UNDEF }, "tig", la_tig },
    { { HTML_4_0 }, { HTML_UNDEF }, "tir", la_tir },
    { { HTML_4_0 }, { HTML_UNDEF }, "tiv", la_tiv },
    { { HTML_4_0 }, { HTML_UNDEF }, "tkl", la_tkl },
    { { HTML_4_0 }, { HTML_UNDEF }, "tlh", la_tlh },
    { { HTML_4_0 }, { HTML_UNDEF }, "tli", la_tli },
    { { HTML_4_0 }, { HTML_UNDEF }, "tmh", la_tmh },
    { { HTML_4_0 }, { HTML_UNDEF }, "tog", la_tog },
    { { HTML_4_0 }, { HTML_UNDEF }, "ton", la_ton },
    { { HTML_4_0 }, { HTML_UNDEF }, "tpi", la_tpi },
    { { HTML_4_0 }, { HTML_UNDEF }, "tsi", la_tsi },
    { { HTML_4_0 }, { HTML_UNDEF }, "tsn", la_tsn },
    { { HTML_4_0 }, { HTML_UNDEF }, "tso", la_tso },
    { { HTML_4_0 }, { HTML_UNDEF }, "tuk", la_tuk },
    { { HTML_4_0 }, { HTML_UNDEF }, "tum", la_tum },
    { { HTML_4_0 }, { HTML_UNDEF }, "tup", la_tup },
    { { HTML_4_0 }, { HTML_UNDEF }, "tur", la_tur },
    { { HTML_4_0 }, { HTML_UNDEF }, "tut", la_tut },
    { { HTML_4_0 }, { HTML_UNDEF }, "tvl", la_tvl },
    { { HTML_4_0 }, { HTML_UNDEF }, "twi", la_twi },
    { { HTML_4_0 }, { HTML_UNDEF }, "tyv", la_tyv },
    { { HTML_4_0 }, { HTML_UNDEF }, "udm", la_udm },
    { { HTML_4_0 }, { HTML_UNDEF }, "uga", la_uga },
    { { HTML_4_0 }, { HTML_UNDEF }, "uig", la_uig },
    { { HTML_4_0 }, { HTML_UNDEF }, "ukr", la_ukr },
    { { HTML_4_0 }, { HTML_UNDEF }, "umb", la_umb },
    { { HTML_4_0 }, { HTML_UNDEF }, "und", la_und },
    { { HTML_4_0 }, { HTML_UNDEF }, "urd", la_urd },
    { { HTML_4_0 }, { HTML_UNDEF }, "uzb", la_uzb },
    { { HTML_4_0 }, { HTML_UNDEF }, "vai", la_vai },
    { { HTML_4_0 }, { HTML_UNDEF }, "ven", la_ven },
    { { HTML_4_0 }, { HTML_UNDEF }, "vie", la_vie },
    { { HTML_4_0 }, { HTML_UNDEF }, "vol", la_vol },
    { { HTML_4_0 }, { HTML_UNDEF }, "vot", la_vot },
    { { HTML_4_0 }, { HTML_UNDEF }, "wak", la_wak },
    { { HTML_4_0 }, { HTML_UNDEF }, "wal", la_wal },
    { { HTML_4_0 }, { HTML_UNDEF }, "war", la_war },
    { { HTML_4_0 }, { HTML_UNDEF }, "was", la_was },
    { { HTML_4_0 }, { HTML_UNDEF }, "wel", la_wel },
    { { HTML_4_0 }, { HTML_UNDEF }, "wen", la_wen },
    { { HTML_4_0 }, { HTML_UNDEF }, "wln", la_wln },
    { { HTML_4_0 }, { HTML_UNDEF }, "wol", la_wol },
    { { HTML_4_0 }, { HTML_UNDEF }, "xal", la_xal },
    { { HTML_4_0 }, { HTML_UNDEF }, "xho", la_xho },
    { { HTML_4_0 }, { HTML_UNDEF }, "yao", la_yao },
    { { HTML_4_0 }, { HTML_UNDEF }, "yap", la_yap },
    { { HTML_4_0 }, { HTML_UNDEF }, "yid", la_yid },
    { { HTML_4_0 }, { HTML_UNDEF }, "yor", la_yor },
    { { HTML_4_0 }, { HTML_UNDEF }, "ypk", la_ypk },
    { { HTML_4_0 }, { HTML_UNDEF }, "zap", la_zap },
    { { HTML_4_0 }, { HTML_UNDEF }, "zbl", la_zbl },
    { { HTML_4_0 }, { HTML_UNDEF }, "zen", la_zen },
    { { HTML_4_0 }, { HTML_UNDEF }, "zgh", la_zgh },
    { { HTML_4_0 }, { HTML_UNDEF }, "zha", la_zha },
    { { HTML_4_0 }, { HTML_UNDEF }, "zho", la_zho },
    { { HTML_4_0 }, { HTML_UNDEF }, "znd", la_znd },
    { { HTML_4_0 }, { HTML_UNDEF }, "zul", la_zul },
    { { HTML_4_0 }, { HTML_UNDEF }, "zun", la_zun },
    { { HTML_4_0 }, { HTML_UNDEF }, "zxx", la_zxx },
    { { HTML_4_0 }, { HTML_UNDEF }, "zza", la_zza },

    // archaic stubs
    { { HTML_PLUS }, { HTML_UNDEF }, "i", la_i } };

void lang_init (nitpick& nits)
{   type_master < t_lang > :: init (nits, lang_symbol_table, sizeof (lang_symbol_table) / sizeof (symbol_entry < html_version, e_lang >)); }
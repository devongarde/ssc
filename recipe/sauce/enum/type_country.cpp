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

struct symbol_entry < html_version, e_country > country_symbol_table [] =
{   { { HTML_PLUS }, { HTML_UNDEF }, "AF", cou_af },
    { { HTML_PLUS }, { HTML_UNDEF }, "AX", cou_ax },
    { { HTML_PLUS }, { HTML_UNDEF }, "AL", cou_al },
    { { HTML_PLUS }, { HTML_UNDEF }, "DZ", cou_dz },
    { { HTML_PLUS }, { HTML_UNDEF }, "AS", cou_as },
    { { HTML_PLUS }, { HTML_UNDEF }, "AD", cou_ad },
    { { HTML_PLUS }, { HTML_UNDEF }, "AO", cou_ao },
    { { HTML_PLUS }, { HTML_UNDEF }, "AI", cou_ai },
    { { HTML_PLUS }, { HTML_UNDEF }, "AQ", cou_aq },
    { { HTML_PLUS }, { HTML_UNDEF }, "AG", cou_ag },
    { { HTML_PLUS }, { HTML_UNDEF }, "AR", cou_ar },
    { { HTML_PLUS }, { HTML_UNDEF }, "AM", cou_am },
    { { HTML_PLUS }, { HTML_UNDEF }, "AW", cou_aw },
    { { HTML_PLUS }, { HTML_UNDEF }, "AU", cou_au },
    { { HTML_PLUS }, { HTML_UNDEF }, "AT", cou_at },
    { { HTML_PLUS }, { HTML_UNDEF }, "AZ", cou_az },
    { { HTML_PLUS }, { HTML_UNDEF }, "BS", cou_bs },
    { { HTML_PLUS }, { HTML_UNDEF }, "BH", cou_bh },
    { { HTML_PLUS }, { HTML_UNDEF }, "BD", cou_bd },
    { { HTML_PLUS }, { HTML_UNDEF }, "BB", cou_bb },
    { { HTML_PLUS }, { HTML_UNDEF }, "BY", cou_by },
    { { HTML_PLUS }, { HTML_UNDEF }, "BE", cou_be },
    { { HTML_PLUS }, { HTML_UNDEF }, "BZ", cou_bz },
    { { HTML_PLUS }, { HTML_UNDEF }, "BJ", cou_bj },
    { { HTML_PLUS }, { HTML_UNDEF }, "BM", cou_bm },
    { { HTML_PLUS }, { HTML_UNDEF }, "BT", cou_bt },
    { { HTML_PLUS }, { HTML_UNDEF }, "BO", cou_bo },
    { { HTML_PLUS }, { HTML_UNDEF }, "BQ", cou_bq },
    { { HTML_PLUS }, { HTML_UNDEF }, "BA", cou_ba },
    { { HTML_PLUS }, { HTML_UNDEF }, "BW", cou_bw },
    { { HTML_PLUS }, { HTML_UNDEF }, "BV", cou_bv },
    { { HTML_PLUS }, { HTML_UNDEF }, "BR", cou_br },
    { { HTML_PLUS }, { HTML_UNDEF }, "IO", cou_io },
    { { HTML_PLUS }, { HTML_UNDEF }, "BN", cou_bn },
    { { HTML_PLUS }, { HTML_UNDEF }, "BG", cou_bg },
    { { HTML_PLUS }, { HTML_UNDEF }, "BF", cou_bf },
    { { HTML_PLUS }, { HTML_UNDEF }, "BI", cou_bi },
    { { HTML_PLUS }, { HTML_UNDEF }, "CV", cou_cv },
    { { HTML_PLUS }, { HTML_UNDEF }, "KH", cou_kh },
    { { HTML_PLUS }, { HTML_UNDEF }, "CM", cou_cm },
    { { HTML_PLUS }, { HTML_UNDEF }, "CA", cou_ca },
    { { HTML_PLUS }, { HTML_UNDEF }, "KY", cou_ky },
    { { HTML_PLUS }, { HTML_UNDEF }, "CF", cou_cf },
    { { HTML_PLUS }, { HTML_UNDEF }, "TD", cou_td },
    { { HTML_PLUS }, { HTML_UNDEF }, "CL", cou_cl },
    { { HTML_PLUS }, { HTML_UNDEF }, "CN", cou_cn },
    { { HTML_PLUS }, { HTML_UNDEF }, "CX", cou_cx },
    { { HTML_PLUS }, { HTML_UNDEF }, "CC", cou_cc },
    { { HTML_PLUS }, { HTML_UNDEF }, "CO", cou_co },
    { { HTML_PLUS }, { HTML_UNDEF }, "KM", cou_km },
    { { HTML_PLUS }, { HTML_UNDEF }, "CD", cou_cd },
    { { HTML_PLUS }, { HTML_UNDEF }, "CG", cou_cg },
    { { HTML_PLUS }, { HTML_UNDEF }, "CK", cou_ck },
    { { HTML_PLUS }, { HTML_UNDEF }, "CR", cou_cr },
    { { HTML_PLUS }, { HTML_UNDEF }, "CI", cou_ci },
    { { HTML_PLUS }, { HTML_UNDEF }, "HR", cou_hr },
    { { HTML_PLUS }, { HTML_UNDEF }, "CU", cou_cu },
    { { HTML_PLUS }, { HTML_UNDEF }, "CW", cou_cw },
    { { HTML_PLUS }, { HTML_UNDEF }, "CY", cou_cy },
    { { HTML_PLUS }, { HTML_UNDEF }, "CZ", cou_cz },
    { { HTML_PLUS }, { HTML_UNDEF }, "DK", cou_dk },
    { { HTML_PLUS }, { HTML_UNDEF }, "DJ", cou_dj },
    { { HTML_PLUS }, { HTML_UNDEF }, "DM", cou_dm },
    { { HTML_PLUS }, { HTML_UNDEF }, "DO", cou_do },
    { { HTML_PLUS }, { HTML_UNDEF }, "EC", cou_ec },
    { { HTML_PLUS }, { HTML_UNDEF }, "EG", cou_eg },
    { { HTML_PLUS }, { HTML_UNDEF }, "SV", cou_sv },
    { { HTML_PLUS }, { HTML_UNDEF }, "GQ", cou_gq },
    { { HTML_PLUS }, { HTML_UNDEF }, "ER", cou_er },
    { { HTML_PLUS }, { HTML_UNDEF }, "EE", cou_ee },
    { { HTML_PLUS }, { HTML_UNDEF }, "SZ", cou_sz },
    { { HTML_PLUS }, { HTML_UNDEF }, "ET", cou_et },
    { { HTML_PLUS }, { HTML_UNDEF }, "FK", cou_fk },
    { { HTML_PLUS }, { HTML_UNDEF }, "FO", cou_fo },
    { { HTML_PLUS }, { HTML_UNDEF }, "FJ", cou_fj },
    { { HTML_PLUS }, { HTML_UNDEF }, "FI", cou_fi },
    { { HTML_PLUS }, { HTML_UNDEF }, "FR", cou_fr },
    { { HTML_PLUS }, { HTML_UNDEF }, "GF", cou_gf },
    { { HTML_PLUS }, { HTML_UNDEF }, "PF", cou_pf },
    { { HTML_PLUS }, { HTML_UNDEF }, "TF", cou_tf },
    { { HTML_PLUS }, { HTML_UNDEF }, "GA", cou_ga },
    { { HTML_PLUS }, { HTML_UNDEF }, "GM", cou_gm },
    { { HTML_PLUS }, { HTML_UNDEF }, "GE", cou_ge },
    { { HTML_PLUS }, { HTML_UNDEF }, "DE", cou_de },
    { { HTML_PLUS }, { HTML_UNDEF }, "GH", cou_gh },
    { { HTML_PLUS }, { HTML_UNDEF }, "GI", cou_gi },
    { { HTML_PLUS }, { HTML_UNDEF }, "GR", cou_gr },
    { { HTML_PLUS }, { HTML_UNDEF }, "GL", cou_gl },
    { { HTML_PLUS }, { HTML_UNDEF }, "GD", cou_gd },
    { { HTML_PLUS }, { HTML_UNDEF }, "GP", cou_gp },
    { { HTML_PLUS }, { HTML_UNDEF }, "GU", cou_gu },
    { { HTML_PLUS }, { HTML_UNDEF }, "GT", cou_gt },
    { { HTML_PLUS }, { HTML_UNDEF }, "GG", cou_gg },
    { { HTML_PLUS }, { HTML_UNDEF }, "GN", cou_gn },
    { { HTML_PLUS }, { HTML_UNDEF }, "GW", cou_gw },
    { { HTML_PLUS }, { HTML_UNDEF }, "GY", cou_gy },
    { { HTML_PLUS }, { HTML_UNDEF }, "HT", cou_ht },
    { { HTML_PLUS }, { HTML_UNDEF }, "HM", cou_hm },
    { { HTML_PLUS }, { HTML_UNDEF }, "VA", cou_va },
    { { HTML_PLUS }, { HTML_UNDEF }, "HN", cou_hn },
    { { HTML_PLUS }, { HTML_UNDEF }, "HK", cou_hk },
    { { HTML_PLUS }, { HTML_UNDEF }, "HU", cou_hu },
    { { HTML_PLUS }, { HTML_UNDEF }, "IS", cou_is },
    { { HTML_PLUS }, { HTML_UNDEF }, "IN", cou_in },
    { { HTML_PLUS }, { HTML_UNDEF }, "ID", cou_id },
    { { HTML_PLUS }, { HTML_UNDEF }, "IR", cou_ir },
    { { HTML_PLUS }, { HTML_UNDEF }, "IQ", cou_iq },
    { { HTML_PLUS }, { HTML_UNDEF }, "IE", cou_ie },
    { { HTML_PLUS }, { HTML_UNDEF }, "IM", cou_im },
    { { HTML_PLUS }, { HTML_UNDEF }, "IL", cou_il },
    { { HTML_PLUS }, { HTML_UNDEF }, "IT", cou_it },
    { { HTML_PLUS }, { HTML_UNDEF }, "JM", cou_jm },
    { { HTML_PLUS }, { HTML_UNDEF }, "JP", cou_jp },
    { { HTML_PLUS }, { HTML_UNDEF }, "JE", cou_je },
    { { HTML_PLUS }, { HTML_UNDEF }, "JO", cou_jo },
    { { HTML_PLUS }, { HTML_UNDEF }, "KZ", cou_kz },
    { { HTML_PLUS }, { HTML_UNDEF }, "KE", cou_ke },
    { { HTML_PLUS }, { HTML_UNDEF }, "KI", cou_ki },
    { { HTML_PLUS }, { HTML_UNDEF }, "KP", cou_kp },
    { { HTML_PLUS }, { HTML_UNDEF }, "KR", cou_kr },
    { { HTML_PLUS }, { HTML_UNDEF }, "KW", cou_kw },
    { { HTML_PLUS }, { HTML_UNDEF }, "KG", cou_kg },
    { { HTML_PLUS }, { HTML_UNDEF }, "LA", cou_la },
    { { HTML_PLUS }, { HTML_UNDEF }, "LV", cou_lv },
    { { HTML_PLUS }, { HTML_UNDEF }, "LB", cou_lb },
    { { HTML_PLUS }, { HTML_UNDEF }, "LS", cou_ls },
    { { HTML_PLUS }, { HTML_UNDEF }, "LR", cou_lr },
    { { HTML_PLUS }, { HTML_UNDEF }, "LY", cou_ly },
    { { HTML_PLUS }, { HTML_UNDEF }, "LI", cou_li },
    { { HTML_PLUS }, { HTML_UNDEF }, "LT", cou_lt },
    { { HTML_PLUS }, { HTML_UNDEF }, "LU", cou_lu },
    { { HTML_PLUS }, { HTML_UNDEF }, "MO", cou_mo },
    { { HTML_PLUS }, { HTML_UNDEF }, "MK", cou_mk },
    { { HTML_PLUS }, { HTML_UNDEF }, "MG", cou_mg },
    { { HTML_PLUS }, { HTML_UNDEF }, "MW", cou_mw },
    { { HTML_PLUS }, { HTML_UNDEF }, "MY", cou_my },
    { { HTML_PLUS }, { HTML_UNDEF }, "MV", cou_mv },
    { { HTML_PLUS }, { HTML_UNDEF }, "ML", cou_ml },
    { { HTML_PLUS }, { HTML_UNDEF }, "MT", cou_mt },
    { { HTML_PLUS }, { HTML_UNDEF }, "MH", cou_mh },
    { { HTML_PLUS }, { HTML_UNDEF }, "MQ", cou_mq },
    { { HTML_PLUS }, { HTML_UNDEF }, "MR", cou_mr },
    { { HTML_PLUS }, { HTML_UNDEF }, "MU", cou_mu },
    { { HTML_PLUS }, { HTML_UNDEF }, "YT", cou_yt },
    { { HTML_PLUS }, { HTML_UNDEF }, "MX", cou_mx },
    { { HTML_PLUS }, { HTML_UNDEF }, "FM", cou_fm },
    { { HTML_PLUS }, { HTML_UNDEF }, "MD", cou_md },
    { { HTML_PLUS }, { HTML_UNDEF }, "MC", cou_mc },
    { { HTML_PLUS }, { HTML_UNDEF }, "MN", cou_mn },
    { { HTML_PLUS }, { HTML_UNDEF }, "ME", cou_me },
    { { HTML_PLUS }, { HTML_UNDEF }, "MS", cou_ms },
    { { HTML_PLUS }, { HTML_UNDEF }, "MA", cou_ma },
    { { HTML_PLUS }, { HTML_UNDEF }, "MZ", cou_mz },
    { { HTML_PLUS }, { HTML_UNDEF }, "MM", cou_mm },
    { { HTML_PLUS }, { HTML_UNDEF }, "NA", cou_na },
    { { HTML_PLUS }, { HTML_UNDEF }, "NR", cou_nr },
    { { HTML_PLUS }, { HTML_UNDEF }, "NP", cou_np },
    { { HTML_PLUS }, { HTML_UNDEF }, "NL", cou_nl },
    { { HTML_PLUS }, { HTML_UNDEF }, "NC", cou_nc },
    { { HTML_PLUS }, { HTML_UNDEF }, "NZ", cou_nz },
    { { HTML_PLUS }, { HTML_UNDEF }, "NI", cou_ni },
    { { HTML_PLUS }, { HTML_UNDEF }, "NE", cou_ne },
    { { HTML_PLUS }, { HTML_UNDEF }, "NG", cou_ng },
    { { HTML_PLUS }, { HTML_UNDEF }, "NU", cou_nu },
    { { HTML_PLUS }, { HTML_UNDEF }, "NF", cou_nf },
    { { HTML_PLUS }, { HTML_UNDEF }, "MP", cou_mp },
    { { HTML_PLUS }, { HTML_UNDEF }, "NO", cou_no },
    { { HTML_PLUS }, { HTML_UNDEF }, "OM", cou_om },
    { { HTML_PLUS }, { HTML_UNDEF }, "PK", cou_pk },
    { { HTML_PLUS }, { HTML_UNDEF }, "PW", cou_pw },
    { { HTML_PLUS }, { HTML_UNDEF }, "PS", cou_ps },
    { { HTML_PLUS }, { HTML_UNDEF }, "PA", cou_pa },
    { { HTML_PLUS }, { HTML_UNDEF }, "PG", cou_pg },
    { { HTML_PLUS }, { HTML_UNDEF }, "PY", cou_py },
    { { HTML_PLUS }, { HTML_UNDEF }, "PE", cou_pe },
    { { HTML_PLUS }, { HTML_UNDEF }, "PH", cou_ph },
    { { HTML_PLUS }, { HTML_UNDEF }, "PN", cou_pn },
    { { HTML_PLUS }, { HTML_UNDEF }, "PL", cou_pl },
    { { HTML_PLUS }, { HTML_UNDEF }, "PT", cou_pt },
    { { HTML_PLUS }, { HTML_UNDEF }, "PR", cou_pr },
    { { HTML_PLUS }, { HTML_UNDEF }, "QA", cou_qa },
    { { HTML_PLUS }, { HTML_UNDEF }, "RE", cou_re },
    { { HTML_PLUS }, { HTML_UNDEF }, "RO", cou_ro },
    { { HTML_PLUS }, { HTML_UNDEF }, "RU", cou_ru },
    { { HTML_PLUS }, { HTML_UNDEF }, "RW", cou_rw },
    { { HTML_PLUS }, { HTML_UNDEF }, "BL", cou_bl },
    { { HTML_PLUS }, { HTML_UNDEF }, "SH", cou_sh },
    { { HTML_PLUS }, { HTML_UNDEF }, "KN", cou_kn },
    { { HTML_PLUS }, { HTML_UNDEF }, "LC", cou_lc },
    { { HTML_PLUS }, { HTML_UNDEF }, "MF", cou_mf },
    { { HTML_PLUS }, { HTML_UNDEF }, "PM", cou_pm },
    { { HTML_PLUS }, { HTML_UNDEF }, "VC", cou_vc },
    { { HTML_PLUS }, { HTML_UNDEF }, "WS", cou_ws },
    { { HTML_PLUS }, { HTML_UNDEF }, "SM", cou_sm },
    { { HTML_PLUS }, { HTML_UNDEF }, "ST", cou_st },
    { { HTML_PLUS }, { HTML_UNDEF }, "SA", cou_sa },
    { { HTML_PLUS }, { HTML_UNDEF }, "SN", cou_sn },
    { { HTML_PLUS }, { HTML_UNDEF }, "RS", cou_rs },
    { { HTML_PLUS }, { HTML_UNDEF }, "SC", cou_sc },
    { { HTML_PLUS }, { HTML_UNDEF }, "SL", cou_sl },
    { { HTML_PLUS }, { HTML_UNDEF }, "SG", cou_sg },
    { { HTML_PLUS }, { HTML_UNDEF }, "SX", cou_sx },
    { { HTML_PLUS }, { HTML_UNDEF }, "SK", cou_sk },
    { { HTML_PLUS }, { HTML_UNDEF }, "SI", cou_si },
    { { HTML_PLUS }, { HTML_UNDEF }, "SB", cou_sb },
    { { HTML_PLUS }, { HTML_UNDEF }, "SO", cou_so },
    { { HTML_PLUS }, { HTML_UNDEF }, "ZA", cou_za },
    { { HTML_PLUS }, { HTML_UNDEF }, "GS", cou_gs },
    { { HTML_PLUS }, { HTML_UNDEF }, "SS", cou_ss },
    { { HTML_PLUS }, { HTML_UNDEF }, "ES", cou_es },
    { { HTML_PLUS }, { HTML_UNDEF }, "LK", cou_lk },
    { { HTML_PLUS }, { HTML_UNDEF }, "SD", cou_sd },
    { { HTML_PLUS }, { HTML_UNDEF }, "SR", cou_sr },
    { { HTML_PLUS }, { HTML_UNDEF }, "SJ", cou_sj },
    { { HTML_PLUS }, { HTML_UNDEF }, "SE", cou_se },
    { { HTML_PLUS }, { HTML_UNDEF }, "CH", cou_ch },
    { { HTML_PLUS }, { HTML_UNDEF }, "SY", cou_sy },
    { { HTML_PLUS }, { HTML_UNDEF }, "TW", cou_tw },
    { { HTML_PLUS }, { HTML_UNDEF }, "TJ", cou_tj },
    { { HTML_PLUS }, { HTML_UNDEF }, "TZ", cou_tz },
    { { HTML_PLUS }, { HTML_UNDEF }, "TH", cou_th },
    { { HTML_PLUS }, { HTML_UNDEF }, "TL", cou_tl },
    { { HTML_PLUS }, { HTML_UNDEF }, "TG", cou_tg },
    { { HTML_PLUS }, { HTML_UNDEF }, "TK", cou_tk },
    { { HTML_PLUS }, { HTML_UNDEF }, "TO", cou_to },
    { { HTML_PLUS }, { HTML_UNDEF }, "TT", cou_tt },
    { { HTML_PLUS }, { HTML_UNDEF }, "TN", cou_tn },
    { { HTML_PLUS }, { HTML_UNDEF }, "TR", cou_tr },
    { { HTML_PLUS }, { HTML_UNDEF }, "TM", cou_tm },
    { { HTML_PLUS }, { HTML_UNDEF }, "TC", cou_tc },
    { { HTML_PLUS }, { HTML_UNDEF }, "TV", cou_tv },
    { { HTML_PLUS }, { HTML_UNDEF }, "UG", cou_ug },
    { { HTML_PLUS }, { HTML_UNDEF }, "UA", cou_ua },
    { { HTML_PLUS }, { HTML_UNDEF }, "AE", cou_ae },
    { { HTML_PLUS }, { HTML_UNDEF }, "GB", cou_gb },
    { { HTML_PLUS }, { HTML_UNDEF }, "UM", cou_um },
    { { HTML_PLUS }, { HTML_UNDEF }, "US", cou_us },
    { { HTML_PLUS }, { HTML_UNDEF }, "UY", cou_uy },
    { { HTML_PLUS }, { HTML_UNDEF }, "UZ", cou_uz },
    { { HTML_PLUS }, { HTML_UNDEF }, "VU", cou_vu },
    { { HTML_PLUS }, { HTML_UNDEF }, "VE", cou_ve },
    { { HTML_PLUS }, { HTML_UNDEF }, "VN", cou_vn },
    { { HTML_PLUS }, { HTML_UNDEF }, "VG", cou_vg },
    { { HTML_PLUS }, { HTML_UNDEF }, "VI", cou_vi },
    { { HTML_PLUS }, { HTML_UNDEF }, "WF", cou_wf },
    { { HTML_PLUS }, { HTML_UNDEF }, "EH", cou_eh },
    { { HTML_PLUS }, { HTML_UNDEF }, "YE", cou_ye },
    { { HTML_PLUS }, { HTML_UNDEF }, "ZM", cou_zm },
    { { HTML_PLUS }, { HTML_UNDEF }, "ZW", cou_zw } };

void country_init (nitpick& nits)
{   type_master < t_country > :: init (nits, country_symbol_table, sizeof (country_symbol_table) / sizeof (symbol_entry < html_version, e_country >)); }
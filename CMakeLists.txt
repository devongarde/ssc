cmake_minimum_required (VERSION 3.24)
set (FULLNAME "Static-Site-Checker")
set (VER 0.2.30)
project (ssc VERSION ${VER} DESCRIPTION ${FULLNAME} LANGUAGES CXX HOMEPAGE_URL "https://dylanharris.org/ssc/")
message (NOTICE "preparing " ${FULLNAME} " ${VER}" )

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_INSTALL_MODE COPY)    # not that it works; despite the command COPY the sodding thing creates links rather than copying files

# expects standard ssc directory structure ...
set (R ${CMAKE_SOURCE_DIR}/recipe)
set (H ${R}/heater)
set (HLP ${R}/help)
set (I ${R}/install)
set (S ${R}/sauce)
set (T ${R}/toast)
set (TT ${T}/ssc-test)
set (TEA ${R}/tea)

set (DD "${DESTDIR}${CMAKE_INSTALL_PREFIX}")
if ("${DD}" MATCHES "")
  if (DEFINED ALTDEST)
    set (DD "${ALTDEST}")
  else ()
    set (DD "/usr")
  endif ()
endif ()

set (INCS "${DD}/include" "${CMAKE_INSTALL_PREFIX}/include")
set (LIBS "${DD}/lib" "${CMAKE_INSTALL_PREFIX}/lib")
set (BV "1.75")
set (HV "1.7")
set (CFT "Debug;Release")

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  message (FATAL_ERROR "Use a Visual Studio solution (https://visualstudio.microsoft.com/downloads/)")
endif ()

# https://stackoverflow.com/questions/11944060/how-to-detect-target-architecture-using-cmake
EXECUTE_PROCESS (COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE)
message (DEBUG "Architecture: ${ARCHITECTURE}")

# Debug / Release (https://riptutorial.com/cmake/example/26702/setting-a-release-debug-configuration)
set (CMAKE_CONFIGURATION_TYPES ${CFT} CACHE STRING "Configs" FORCE)

if (DEFINED CMAKE_BUILD_TYPE)
  set_property (CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES})
endif ()

set (IMPLICITFALL ";-Wno-implicit-fallthrough")
set (NOINDENTLIE ";-Wno-misleading-indentation")
set (TEMPLATEDEPTH "")

set (XTEST "ssc-test")
set (XSHELL "ssc")
set (XWAX "ssc-wx")
set (XAPP ${FULLNAME})
set (XAPP2 ${XAPP}.app)

# shush, don't tell auntie
set (TOASTERS ${S}/test/ssc-test.cpp ${H}/main/version.h ${H}/feedback/nitnames.h ${S}/feedback/nitnames.cpp)

set (HEATERS
        ${H}/attribute/attr.h ${H}/attribute/attr_state.h ${H}/attribute/attribute.h ${H}/attribute/attribute_classes.h ${H}/attribute/attributes.h
            ${H}/attribute/avm.h ${H}/attribute/avm_data.h ${H}/attribute/namespace.h
        ${H}/base/base.h ${H}/base/reldef.h ${H}/base/sz.h ${H}/base/type_base.h ${H}/base/type_case.h ${H}/base/type_core.h ${H}/base/type_master.h
        ${H}/compound/compound.h ${H}/compound/type_all_of.h ${H}/compound/type_one_of.h ${H}/compound/type_some_of.h ${H}/compound/type_compound.h
            ${H}/compound/type_compounded.h ${H}/compound/type_csses.h ${H}/compound/type_fn.h ${H}/compound/type_httpequivs.h
            ${H}/compound/type_jsonics.h ${H}/compound/type_langs.h ${H}/compound/type_maths.h ${H}/compound/type_measures.h
            ${H}/compound/type_microdatas.h ${H}/compound/type_microformats.h ${H}/compound/type_mimes.h ${H}/compound/type_numerics.h
            ${H}/compound/type_svgs.h ${H}/compound/type_sz.h ${H}/compound/type_van.h ${H}/compound/type_varied.h
        ${H}/coop/fred.h ${H}/coop/kew.h ${H}/coop/knickers.h ${H}/coop/lox.h ${H}/coop/tls.h
        ${H}/css/arguments.h ${H}/css/css.h ${H}/css/css_attribute.h ${H}/css/css_class.h ${H}/css/css_element.h ${H}/css/css_parse.h ${H}/css/css_pre.h
            ${H}/css/css_state.h ${H}/css/decoration.h ${H}/css/descriptor.h ${H}/css/descriptor_classes.h ${H}/css/descriptors.h ${H}/css/distilled.h
            ${H}/css/ffv.h ${H}/css/ffvs.h ${H}/css/flags.h ${H}/css/fn.h ${H}/css/global.h ${H}/css/group.h ${H}/css/id.h ${H}/css/media.h
            ${H}/css/medium.h ${H}/css/property.h ${H}/css/properties.h ${H}/css/property_classes.h ${H}/css/rule.h ${H}/css/rules.h
            ${H}/css/selector.h ${H}/css/selectors.h ${H}/css/statement.h ${H}/css/statements.h ${H}/css/typed_property.h ${H}/css/value.h
            ${H}/css/value_types.h ${H}/css/weight.h  
        ${H}/element/elem.h ${H}/element/element.h ${H}/element/element_attribute.h ${H}/element/element_classes.h ${H}/element/parentage.h
            ${H}/element/state.h
        ${H}/enum/enumerated.h ${H}/enum/type_1.h ${H}/enum/type_2.h ${H}/enum/type_3.h ${H}/enum/type_4.h ${H}/enum/type_aria.h
            ${H}/enum/type_class.h ${H}/enum/type_colour.h ${H}/enum/type_country.h ${H}/enum/type_enum.h ${H}/enum/type_enum_vec.h ${H}/enum/type_lang.h
            ${H}/enum/type_mime.h ${H}/enum/type_rel.h ${H}/enum/type_xmlns.h
        ${H}/feedback/nit.h ${H}/feedback/nitnames.h ${H}/feedback/nitout.h ${H}/feedback/nitpick.h
        ${H}/icu/charset.h ${H}/icu/converter.h ${H}/icu/lingo.h ${H}/icu/wrapper.h
        ${H}/main/abort.h ${H}/main/args.h ${H}/main/balloon.h ${H}/main/context.h ${H}/main/enum.h ${H}/main/include.h ${H}/main/options.h
            ${H}/main/output.h ${H}/main/server.h ${H}/main/standard.h ${H}/main/version.h
        ${H}/microdata/microdata_export.h ${H}/microdata/microdata_itemid.h ${H}/microdata/microdata_itemprop.h ${H}/microdata/microdata_itemscope.h
            ${H}/microdata/microdata_itemtype.h
        ${H}/microformat/connection.h ${H}/microformat/family.h ${H}/microformat/field.h ${H}/microformat/microformat.h
            ${H}/microformat/microformat_classes.h ${H}/microformat/microformat_constructor.h ${H}/microformat/microformat_export.h
            ${H}/microformat/microformat_export_rel.h ${H}/microformat/microformat_properties.h ${H}/microformat/microformats.h
            ${H}/microformat/microformats_ptr.h ${H}/microformat/prop.h ${H}/microformat/property.h ${H}/microformat/property_classes.h
            ${H}/microformat/property_value.h ${H}/microformat/sibling.h
        ${H}/ontology/jsonld.h ${H}/ontology/ontology_hierarchy.h ${H}/ontology/ontology_name.h ${H}/ontology/ontology_property.h
            ${H}/ontology/ontology_structure.h ${H}/ontology/ontology_type.h ${H}/ontology/ontology_version.h
        ${H}/parser/ads.h ${H}/parser/colonic.h ${H}/parser/efficiency.h ${H}/parser/html_version.h ${H}/parser/jsonic.h
            ${H}/parser/parse_abb.h ${H}/parser/parse_attribute.h ${H}/parser/parse_attributes.h ${H}/parser/parse_brac_ket.h
            ${H}/parser/parse_bracs_ket.h ${H}/parser/parse_element.h ${H}/parser/parse_elements.h ${H}/parser/parse_ssi.h
            ${H}/parser/pattern.h ${H}/parser/robotic.h ${H}/parser/security.h ${H}/parser/text.h ${H}/parser/text-data.h
            ${H}/parser/xhtml_xml.h
        ${H}/rdf/rdf.h ${H}/rdf/rdfa_prop.h ${H}/rdf/rdfa_type.h
        ${H}/simple/simple.h ${H}/simple/type_autocomplete.h ${H}/simple/type_css.h ${H}/simple/type_currency.h
            ${H}/simple/type_httpequiv.h ${H}/simple/type_jsonic.h ${H}/simple/type_media.h ${H}/simple/type_metaname.h ${H}/simple/type_rdf.h
            ${H}/simple/type_reals.h ${H}/simple/type_relational.h ${H}/simple/type_time.h ${H}/simple/type_url.h ${H}/simple/type_basic.h
            ${H}/simple/type_id.h ${H}/simple/type_layout.h ${H}/simple/type_math.h ${H}/simple/type_measure.h ${H}/simple/type_microdata.h
            ${H}/simple/type_microformat.h ${H}/simple/type_misc.h ${H}/simple/type_numeric.h ${H}/simple/type_svg.h
        ${H}/spell/spell.h ${H}/spell/phrase.h
        ${H}/stats/stats.h ${H}/stats/stats0.h ${H}/stats/stats1.h ${H}/stats/stats2.h ${H}/stats/stats3.h ${H}/stats/stats4.h ${H}/stats/stats5.h
            ${H}/stats/stats6.h ${H}/stats/stats_impl.h
        ${H}/symbol/nstr.h ${H}/symbol/symbol.h ${H}/symbol/symbol_entry.h ${H}/symbol/symbol_key.h ${H}/symbol/symbol_store.h ${H}/symbol/symbol_table.h
        ${H}/type/type.h ${H}/type/type_csp.h
        ${H}/url/fetch.h ${H}/url/url.h ${H}/url/url_parameters.h ${H}/url/url_protocol.h ${H}/url/url_sanitise.h ${H}/url/url_scheme.h
            ${H}/url/url_schemes.h ${H}/url/wacky.h
        ${H}/utility/bigvector.h ${H}/utility/bitset.h ${H}/utility/byteorder.h ${H}/utility/cache.h ${H}/utility/category.h ${H}/utility/common.h
			${H}/utility/fileio.h ${H}/utility/filesystem.h ${H}/utility/lexical.h ${H}/utility/list.h ${H}/utility/quote.h ${H}/utility/ssl.h
			${H}/utility/tuple.h
        ${H}/webpage/corpus.h ${H}/webpage/crosslink.h ${H}/webpage/directory.h ${H}/webpage/external.h ${H}/webpage/fileindex.h ${H}/webpage/headers.h
            ${H}/webpage/id.h ${H}/webpage/page.h ${H}/webpage/q.h ${H}/webpage/required.h ${H}/webpage/root.h ${H}/webpage/vtt.h
    )
set (SAUCE
        ${S}/attribute/attr.cpp ${S}/attribute/attr_state.cpp ${S}/attribute/attribute_constructor.cpp ${S}/attribute/attribute.cpp
            ${S}/attribute/attributes.cpp ${S}/attribute/avm.cpp ${S}/attribute/avm_data_a.cpp ${S}/attribute/avm_data_b.cpp ${S}/attribute/avm_data_c.cpp
            ${S}/attribute/avm_data_d.cpp ${S}/attribute/avm_data_e.cpp ${S}/attribute/avm_data_f1.cpp ${S}/attribute/avm_data_f2.cpp
            ${S}/attribute/avm_data_g.cpp ${S}/attribute/avm_data_h.cpp
            ${S}/attribute/avm_data_i.cpp ${S}/attribute/avm_data_k.cpp ${S}/attribute/avm_data_l.cpp ${S}/attribute/avm_data_m1.cpp
            ${S}/attribute/avm_data_m2.cpp ${S}/attribute/avm_data_n.cpp ${S}/attribute/avm_data_o.cpp ${S}/attribute/avm_data_p.cpp
            ${S}/attribute/avm_data_q.cpp ${S}/attribute/avm_data_r.cpp ${S}/attribute/avm_data_s.cpp ${S}/attribute/avm_data_t1.cpp
            ${S}/attribute/avm_data_t2.cpp ${S}/attribute/avm_data_u.cpp ${S}/attribute/avm_data_v.cpp ${S}/attribute/avm_data_w.cpp
            ${S}/attribute/avm_data_x.cpp ${S}/attribute/avm_data_rdf.cpp ${S}/attribute/namespace.cpp
        ${S}/base/type_base.cpp ${S}/base/type_case.cpp ${S}/base/type_core.cpp ${S}/base/type_master.cpp
        ${S}/coop/fred.cpp ${S}/coop/kew.cpp ${S}/coop/knickers.cpp ${S}/coop/lox.cpp ${S}/coop/tls.cpp
        ${S}/compound/type_csses.cpp ${S}/compound/type_mimes.cpp ${S}/compound/type_van.cpp ${S}/compound/type_varied.cpp
        ${S}/css/arguments.cpp ${S}/css/css.cpp ${S}/css/css_attribute.cpp ${S}/css/css_class.cpp ${S}/css/css_element.cpp ${S}/css/css_id.cpp
            ${S}/css/css_parse.cpp ${S}/css/css_state.cpp ${S}/css/decoration.cpp ${S}/css/descriptor.cpp ${S}/css/descriptor_constructor.cpp
            ${S}/css/descriptors.cpp ${S}/css/distilled.cpp ${S}/css/ffv.cpp ${S}/css/ffvs.cpp ${S}/css/fn.cpp ${S}/css/global.cpp ${S}/css/group.cpp
            ${S}/css/media.cpp ${S}/css/medium.cpp ${S}/css/property.cpp ${S}/css/properties.cpp ${S}/css/property_constructor.cpp ${S}/css/rule.cpp
            ${S}/css/rules.cpp ${S}/css/selector.cpp ${S}/css/selectors.cpp ${S}/css/statement.cpp ${S}/css/statements.cpp ${S}/css/typed_property.cpp
            ${S}/css/value.cpp ${S}/css/value2.cpp ${S}/css/value_types_0_1.cpp ${S}/css/value_types_2_9.cpp ${S}/css/value_types_a_1.cpp
            ${S}/css/value_types_a_2.cpp ${S}/css/value_types_a_3.cpp ${S}/css/value_types_a_4.cpp ${S}/css/value_types_a_5.cpp ${S}/css/value_types_b_1.cpp
			${S}/css/value_types_b_2.cpp ${S}/css/value_types_c_1.cpp ${S}/css/value_types_c_2.cpp ${S}/css/value_types_c_3.cpp ${S}/css/value_types_c_4.cpp
            ${S}/css/value_types_c_5.cpp ${S}/css/value_types_css_a_1.cpp ${S}/css/value_types_css_a_2.cpp ${S}/css/value_types_css_a_3.cpp
			${S}/css/value_types_css_b_1.cpp ${S}/css/value_types_css_b_2.cpp ${S}/css/value_types_css_b_3.cpp ${S}/css/value_types_css_b_4.cpp
			${S}/css/value_types_css_c_1.cpp ${S}/css/value_types_css_c_2.cpp ${S}/css/value_types_css_c_3.cpp ${S}/css/value_types_css_c_4.cpp
			${S}/css/value_types_css_c_5.cpp ${S}/css/value_types_css_d.cpp ${S}/css/value_types_css_e.cpp ${S}/css/value_types_css_f_1.cpp
			${S}/css/value_types_css_f_2.cpp ${S}/css/value_types_css_f_3.cpp ${S}/css/value_types_css_fn_1.cpp ${S}/css/value_types_css_fn_2.cpp
			${S}/css/value_types_css_g_h.cpp ${S}/css/value_types_css_i_1.cpp ${S}/css/value_types_css_i_2.cpp ${S}/css/value_types_css_j_k.cpp
			${S}/css/value_types_css_l_1.cpp ${S}/css/value_types_css_l_2.cpp ${S}/css/value_types_css_l_3.cpp ${S}/css/value_types_css_m_n.cpp
			${S}/css/value_types_css_o.cpp ${S}/css/value_types_css_p_1.cpp ${S}/css/value_types_css_p_q.cpp ${S}/css/value_types_css_r_1.cpp
			${S}/css/value_types_css_r_2.cpp ${S}/css/value_types_css_s_1.cpp ${S}/css/value_types_css_s_2.cpp ${S}/css/value_types_css_s_3.cpp
			${S}/css/value_types_css_t_1.cpp ${S}/css/value_types_css_t_2.cpp ${S}/css/value_types_css_t_3.cpp ${S}/css/value_types_css_t_4.cpp
			${S}/css/value_types_css_u.cpp ${S}/css/value_types_css_v.cpp ${S}/css/value_types_css_w_z.cpp ${S}/css/value_types_d_1.cpp ${S}/css/value_types_d_2.cpp
			${S}/css/value_types_e.cpp ${S}/css/value_types_f_1.cpp ${S}/css/value_types_f_2.cpp ${S}/css/value_types_f_3.cpp ${S}/css/value_types_g.cpp
            ${S}/css/value_types_h.cpp ${S}/css/value_types_i_1.cpp ${S}/css/value_types_i_2.cpp ${S}/css/value_types_i_3.cpp ${S}/css/value_types_j_k.cpp
			${S}/css/value_types_l_1.cpp ${S}/css/value_types_l_2.cpp ${S}/css/value_types_l_3.cpp ${S}/css/value_types_m_1.cpp ${S}/css/value_types_m_2.cpp
			${S}/css/value_types_m_3.cpp ${S}/css/value_types_m_4.cpp ${S}/css/value_types_m_5.cpp ${S}/css/value_types_m_6.cpp ${S}/css/value_types_n.cpp
            ${S}/css/value_types_o.cpp ${S}/css/value_types_p_1.cpp ${S}/css/value_types_p_2.cpp ${S}/css/value_types_p_3.cpp ${S}/css/value_types_p_4.cpp
			${S}/css/value_types_r_1.cpp ${S}/css/value_types_r_2.cpp ${S}/css/value_types_r_3.cpp ${S}/css/value_types_r_4.cpp ${S}/css/value_types_r_5.cpp
			${S}/css/value_types_r_6.cpp ${S}/css/value_types_s_1.cpp ${S}/css/value_types_s_2.cpp ${S}/css/value_types_s_3.cpp ${S}/css/value_types_s_4.cpp
			${S}/css/value_types_s_5.cpp ${S}/css/value_types_s_6.cpp ${S}/css/value_types_t_1.cpp ${S}/css/value_types_t_2.cpp ${S}/css/value_types_u_1.cpp
			${S}/css/value_types_u_2.cpp ${S}/css/value_types_v_1.cpp ${S}/css/value_types_v_2.cpp ${S}/css/value_types_w.cpp ${S}/css/value_types_x_1.cpp
			${S}/css/value_types_x_2.cpp ${S}/css/value_types_y_z.cpp ${S}/css/weight.cpp 
        ${S}/element/elem.cpp ${S}/element/element.cpp ${S}/element/element_abcd.cpp ${S}/element/element_aria.cpp ${S}/element/element_attributes.cpp
            ${S}/element/element_classes.cpp ${S}/element/element_efghi.cpp ${S}/element/element_examine.cpp ${S}/element/element_input.cpp
            ${S}/element/element_jkl.cpp ${S}/element/element_microdata.cpp ${S}/element/element_microformats.cpp ${S}/element/element_mno.cpp
            ${S}/element/element_pqr.cpp ${S}/element/element_rdfa.cpp ${S}/element/element_s.cpp ${S}/element/element_tuvwxyz.cpp
            ${S}/element/parentage.cpp ${S}/element/state.cpp
        ${S}/enum/type_aria.cpp ${S}/enum/type_charset.cpp ${S}/enum/type_class.cpp ${S}/enum/type_colour.cpp ${S}/enum/type_country.cpp
            ${S}/enum/type_enum.cpp ${S}/enum/type_mime.cpp ${S}/enum/type_lang.cpp ${S}/enum/type_property.cpp ${S}/enum/type_rel.cpp
            ${S}/enum/type_xmlns.cpp
        ${S}/feedback/nit.cpp ${S}/feedback/nitnames.cpp ${S}/feedback/nitout.cpp ${S}/feedback/nitpick.cpp
        ${S}/icu/charset.cpp ${S}/icu/converter.cpp ${S}/icu/lingo.cpp ${S}/icu/wrapper.cpp
        ${S}/main/abort.cpp ${S}/main/context.cpp ${S}/main/options.cpp ${S}/main/output.cpp ${S}/main/ssc.cpp ${S}/main/server.cpp ${S}/main/standard.cpp
            ${S}/main/version.cpp
        ${S}/microdata/microdata_export.cpp ${S}/microdata/microdata_itemid.cpp ${S}/microdata/microdata_itemprop.cpp ${S}/microdata/microdata_itemscope.cpp
            ${S}/microdata/microdata_itemtype.cpp
        ${S}/microformat/family.cpp ${S}/microformat/field.cpp ${S}/microformat/microformat_constructor.cpp ${S}/microformat/microformat_export.cpp
            ${S}/microformat/microformats.cpp ${S}/microformat/property_value.cpp ${S}/microformat/sibling.cpp
        ${S}/ontology/jsonld.cpp ${S}/ontology/ontology_hierarchy.cpp ${S}/ontology/ontology_name.cpp ${S}/ontology/ontology_property.cpp
            ${S}/ontology/ontology_structure.cpp ${S}/ontology/ontology_type.cpp ${S}/ontology/ontology_version.cpp
        ${S}/parser/ads.cpp ${S}/parser/colonic.cpp ${S}/parser/efficiency.cpp ${S}/parser/html_version.cpp ${S}/parser/jsonic.cpp
            ${S}/parser/parse_attribute.cpp ${S}/parser/parse_attributes.cpp ${S}/parser/parse_brac_ket.cpp ${S}/parser/parse_bracs_ket.cpp 
            ${S}/parser/parse_element.cpp ${S}/parser/parse_elements.cpp ${S}/parser/parse_ssi.cpp ${S}/parser/pattern.cpp ${S}/parser/robotic.cpp
            ${S}/parser/security.cpp ${S}/parser/text.cpp ${S}/parser/text-data.cpp ${S}/parser/xhtml_xml.cpp
        ${S}/rdf/rdf.cpp ${S}/rdf/rdfa_prop.cpp ${S}/rdf/rdfa_type.cpp
        ${S}/simple/type_autocomplete.cpp ${S}/simple/type_basic.cpp ${S}/simple/type_css.cpp ${S}/simple/type_currency.cpp ${S}/simple/type_d.cpp
            ${S}/simple/type_httpequiv.cpp ${S}/simple/type_id.cpp ${S}/simple/type_jsonic.cpp ${S}/simple/type_intent.cpp ${S}/simple/type_layout.cpp
            ${S}/base/type_master.cpp ${S}/simple/type_measure.cpp ${S}/simple/type_media.cpp ${S}/simple/type_metaname.cpp ${S}/simple/type_microdata.cpp
            ${S}/simple/type_misc.cpp ${S}/simple/type_numeric.cpp ${S}/simple/type_paint.cpp ${S}/simple/type_rdf.cpp ${S}/simple/type_reals.cpp
            ${S}/simple/type_sgml.cpp ${S}/simple/type_svg_feature.cpp ${S}/simple/type_time.cpp ${S}/simple/type_transform.cpp ${S}/compound/type_varied.cpp
        ${S}/spell/spell.cpp ${S}/spell/nixspell.cpp ${S}/spell/winspell.cpp
        ${S}/stats/stats.cpp ${S}/stats/stats_impl.cpp
        ${S}/symbol/nstr.cpp ${S}/symbol/symbol.cpp
        ${S}/type/type.cpp ${S}/type/type_csp.cpp
        ${S}/url/fetch.cpp ${S}/url/url.cpp ${S}/url/url_parameters.cpp ${S}/url/url_protocol.cpp ${S}/url/url_sanitise.cpp ${S}/url/url_scheme.cpp
            ${S}/url/wacky.cpp
        ${S}/utility/byteorder.cpp ${S}/utility/cache.cpp ${S}/utility/category.cpp ${S}/utility/common.cpp ${S}/utility/fileio.cpp ${S}/utility/filesystem.cpp
			${S}/utility/list.cpp ${S}/utility/quote.cpp
        ${S}/webpage/corpus.cpp ${S}/webpage/crosslink.cpp ${S}/webpage/directory.cpp ${S}/webpage/external.cpp ${S}/webpage/fileindex.cpp
            ${S}/webpage/headers.cpp ${S}/webpage/id.cpp ${S}/webpage/page.cpp ${S}/webpage/q.cpp ${S}/webpage/required.cpp ${S}/webpage/root.cpp
            ${S}/webpage/vtt.cpp
    )
set (GOOEY
        ${H}/gui/gui-app.h ${H}/gui/gui-css.h ${H}/gui/gui-ctrl.h ${H}/gui/gui-ctrls.h ${H}/gui/gui-dialogue.h ${H}/gui/gui-data.h ${H}/gui/gui-frame.h
            ${H}/gui/gui-general.h ${H}/gui/gui-html.h ${H}/gui/gui-icon.h ${H}/gui/gui-link.h ${H}/gui/gui-listedit.h ${H}/gui/gui-menu.h
            ${H}/gui/gui-nits.h ${H}/gui/gui-ontology.h ${H}/gui/gui-output.h ${H}/gui/gui-screen.h ${H}/gui/gui-shadow.h ${H}/gui/gui-site.h
            ${H}/gui/gui-snippet.h ${H}/gui/gui-spell.h ${H}/gui/gui-spex.h ${H}/gui/gui-ssi.h ${H}/gui/gui-stats.h ${H}/gui/gui-summarise.h
            ${H}/gui/gui-validation.h ${H}/gui/gui-welcome.h
        ${S}/gui/gui-app.cpp ${S}/gui/gui-css.cpp ${S}/gui/gui-ctrl.cpp ${S}/gui/gui-ctrls.cpp ${S}/gui/gui-data.cpp ${S}/gui/gui-dialogue.cpp
            ${S}/gui/gui-frame.cpp ${S}/gui/gui-general.cpp ${S}/gui/gui-html.cpp ${S}/gui/gui-icon.cpp ${S}/gui/gui-link.cpp ${S}/gui/gui-listedit.cpp
            ${S}/gui/gui-menu.cpp ${S}/gui/gui-nits.cpp ${S}/gui/gui-ontology.cpp ${S}/gui/gui-output.cpp ${S}/gui/gui-screen.cpp ${S}/gui/gui-shadow.cpp
            ${S}/gui/gui-site.cpp ${S}/gui/gui-snippet.cpp ${S}/gui/gui-spell.cpp ${S}/gui/gui-snippet.cpp ${S}/gui/gui-spex.cpp ${S}/gui/gui-ssi.cpp
            ${S}/gui/gui-stats.cpp ${S}/gui/gui-summarise.cpp ${S}/gui/gui-validation.cpp ${S}/gui/gui-welcome.cpp
    )

set (PREHEAD ${H}/main/include.h)
set (INCDIR ${H} ${INCS})

set (CDEF_TEST SSC_TEST)
set (CDEF_SHELL "")
set (CDEF_WAX WX)
set (CDEF_PROD "")
set (CDEF_ALL "")
set (CDEF_APP SSC_APP)

set (LLTEST "")
set (LLSHELL "")
set (LLWAX "")
set (LLAPP "")
set (LLALL "")
set (LLPROD "")
set (LLGOOEY "")

set (TARGET_OS ${CMAKE_SYSTEM})

if (${CMAKE_SYSTEM_NAME} MATCHES "OpenBSD")
    set (DOCU "${DD}/share/doc/ssc")
    set (D "${DD}/bin")
    set (INC ${INCS})
    set (LD ${LIBS})
    set (CDEF_ALL ${CDEF_ALL} NO_PCF_STR UNIX OBSD)
    set (NOX "1")
    set (NOICU "1")
    set (Boost_USE_STATIC_LIBS ON)
    if (${CMAKE_SYSTEM_VERSION} VERSION_GREATER "7.8")
        message (FATAL_ERROR "apologies, but ssc has only been tested against OpenBSD versions 6.9 to 7.8")
    elseif (${CMAKE_SYSTEM_VERSION} VERSION_GREATER_EQUAL "7.0")
        set (CDEF_PROD ${CDEF_PROD} HUNSPELL) 
    elseif (${CMAKE_SYSTEM_VERSION} MATCHES "6.9")
        set (BV "1.70")
        set (CDEF_PROD ${CDEF_PROD} HUNSPELL) 
        set (NJ "1")
    elseif (${CMAKE_SYSTEM_VERSION} VERSION_LESS "6.9")
        message (FATAL_ERROR "apologies, but ssc requires OpenBSD 6.9 or later")
    else ()
        message (WARNING "untested version of OpenBSD")
        set (TARGET_OS ${CMAKE_SYSTEM_NAME})
        set (CDEF_PROD ${CDEF_PROD} OMG)
        set (NJ "1")
        set (NS "1")
    endif ()
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    if (DEFINED FLAVOUR)
        SET (LSB_RELEASE_ID_SHORT "${FLAVOUR}")
    elseif (DEFINED ENV{FLAVOUR})
        SET (LSB_RELEASE_ID_SHORT $ENV{FLAVOUR})
    else ()
        find_program (LSB_RELEASE lsb_release)
        execute_process (COMMAND ${LSB_RELEASE} -is
            OUTPUT_VARIABLE LSB_RELEASE_ID_SHORT OUTPUT_STRIP_TRAILING_WHITESPACE
        )
    endif ()
    if (DEFINED FLAVOUR_VER)
        SET (LSB_RELEASE_VER_SHORT "${FLAVOUR_VER}")
    elseif (DEFINED ENV{FLAVOUR_VER})
        SET (LSB_RELEASE_VER_SHORT $ENV{FLAVOUR_VER})
    else ()
        find_program (LSB_RELEASE lsb_release)
        execute_process (COMMAND ${LSB_RELEASE} -rs
        OUTPUT_VARIABLE LSB_RELEASE_VER_SHORT OUTPUT_STRIP_TRAILING_WHITESPACE)
    endif ()
    set (CDEF_ALL ${CDEF_ALL} LINUX UNIX)
    set (CDEF_PROD ${CDEF_PROD} OMG BOOST_BIND_GLOBAL_PLACEHOLDERS)
    if ("${LSB_RELEASE_ID_SHORT}" STREQUAL "")
        set (TARGET_OS "Linux")
        message (WARNING "Unknown flavour of Linux; please install lsb_release, or specify FLAVOUR and FLAVOUR_VER")
     else ()
        set (TARGET_OS "${LSB_RELEASE_ID_SHORT} ${LSB_RELEASE_VER_SHORT}")
    endif ()
    set (NJ "1") 
    set (NS "1")
    set (BV "1.70")
    set (D "${DD}/bin")
    set (DOCU "${DD}/../share/doc/ssc")
    set (INC ${INCS} "/usr/include/" "/usr/local/include/" "/usr/include/x86_64-linux-gnu/")
    set (LD ${LIBS} "/usr/lib64/")
    if (${LSB_RELEASE_ID_SHORT} MATCHES "Fedora")
        set (Boost_USE_STATIC_LIBS OFF)
        message ("Boost it'll find 'em if you're lucky libraries")
    else ()
        set (Boost_USE_STATIC_LIBS ON)
        message ("Boost static libraries")
    endif ()
    set (NOX "1")
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set (D "${DD}/local/bin")
    set (DOCU "${DD}/local/share/doc/ssc")
    set (INC ${INCS} "/usr/local/include/" "/opt/local/include")
    set (LD ${LIBS} "/usr/local/lib" "/opt/local/lib")
    set (CDEF_ALL ${CDEF_ALL} UNIX DARWIN)
    set (NO_GSL "1")   # macports installs gtest & cmake makes a Makefile for GSL that can't find gtest
    set (MACOSX_RPATH "/usr/local/lib")
    set (MC ${CMAKE_BINARY_DIR}/${XAPP2}/Contents)
    set (Boost_USE_STATIC_LIBS ON)
    set (NOX "0")
    if (${CMAKE_SYSTEM} MATCHES "Darwin-25")
        set (TARGET_OS "Tahoe")
        set (CDEF_PROD ${CDEF_PROD} CLEAN_SHAREDPTR_ARRAY ORDERED)
		set (BV "1.89") # CMake on MacOS Tacky annoyingly barfs on old versions of boost::system
		set (NO_BOO_SYS "1")
        if (${ARCHITECTURE} MATCHES "x86_64")
            set (NJ "1")
        endif ()
        set (SIGNING "1")
    elseif (${CMAKE_SYSTEM} MATCHES "Darwin-24")
        set (TARGET_OS "Sequoia")
        set (CDEF_PROD ${CDEF_PROD} CLEAN_SHAREDPTR_ARRAY ORDERED)
        if (${ARCHITECTURE} MATCHES "x86_64")
            set (NJ "1")
        endif ()
        set (SIGNING "1")
    elseif (${CMAKE_SYSTEM} MATCHES "Darwin-23")
        set (TARGET_OS "Sonoma")
        set (CDEF_PROD ${CDEF_PROD} HUNSPELL CLEAN_SHAREDPTR_ARRAY ORDERED)
    elseif (${CMAKE_SYSTEM} MATCHES "Darwin-22")
        set (TARGET_OS "Ventura")
        set (CDEF_PROD ${CDEF_PROD} HUNSPELL CLEAN_SHAREDPTR_ARRAY ORDERED)
    elseif (${CMAKE_SYSTEM} MATCHES "Darwin-21")
        set (TARGET_OS "Monterey")
        set (CDEF_PROD ${CDEF_PROD} HUNSPELL CLEAN_SHAREDPTR_ARRAY ORDERED)
    elseif (${CMAKE_SYSTEM} MATCHES "Darwin-20")
        set (TARGET_OS "Big Sur")
        set (CDEF_PROD ${CDEF_PROD} HUNSPELL)
    elseif (${CMAKE_SYSTEM} MATCHES "Darwin-19")
        set (TARGET_OS "Catalina")
        set (CDEF_PROD ${CDEF_PROD} HUNSPELL)
        set (NJ "1")
    elseif (${CMAKE_SYSTEM} MATCHES "Darwin-18")
        set (TARGET_OS "Mojave")
        set (NOINDENTLIE "")
        set (NJ "1")
        set (NS "1")
    elseif (${CMAKE_SYSTEM_VERSION} VERSION_LESS_EQUAL "17")
        message (FATAL_ERROR "apologies, but ssc requires one of MacOS versions Tahoe to Mojave")
    else ()
        message (WARNING "unknown, untested MacOS")
        set (TARGET_OS "Darwin?")
    endif ()

    if (${CMAKE_BUILD_TYPE} MATCHES "Release")
        # can't remember where I found this :-(
        find_program (DSYMUTIL_PROGRAM dsymutil)
        if (DSYMUTIL_PROGRAM)
            foreach (lang C CXX)
                foreach (var LINK_EXECUTABLE CREATE_SHARED_LIBRARY)
                    set (CMAKE_${lang}_${var} "${CMAKE_${lang}_${var}}" "${DSYMUTIL_PROGRAM} <TARGET>")
                endforeach()
            endforeach()
        endif()
    endif()
else ()
    message (WARNING "unknown, untested, system: good luck")
    set (TARGET_OS "unknown")
    set (D "~/bin")
    set (CDEF_PROD ${CDEF_PROD} OMG NO_PCF_STR)
    set (NJ "1")
    set (NS "1")
    set (NOX "1")
endif ()

message (VERBOSE ${TARGET_OS})

set (${PROJ_NAME}_PATH_INSTALL ${D} CACHE PATH "This directory contains an installation path")
set (CMAKE_DEBUG_POSTFIX "d")

if (${NJ} MATCHES "1")
  set (CDEF_ALL ${CDEF_ALL} NO_JSONIC)
endif ()

if (${NOICU} MATCHES "1")
    set (CDEF_ALL ${CDEF_ALL} NOICU)
endif ()

if (${NJ} MATCHES "1") # if only NOT MATCHES worked
else ()
    message (VERBOSE "jsonic")
    set (BOOLIB ${BOOLIB} json)
endif ()

set (Boost_USE_MULTI_THREADED ON)

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set (Boost_USE_DEBUG_LIBS ON)
    set (Boost_USE_DEBUG_RUNTIME ON)
else ()
    set (Boost_USE_DEBUG_LIBS OFF)
    set (Boost_USE_DEBUG_RUNTIME OFF)
endif ()

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set (Boost_USE_DEBUG_LIBS ON)
    set (Boost_USE_DEBUG_RUNTIME ON)
else ()
    set (Boost_USE_DEBUG_LIBS OFF)
    set (Boost_USE_DEBUG_RUNTIME OFF)
endif ()

if (${NO_BOO_SYS} MATCHES "1")
    set (BOOLIB atomic chrono container date_time filesystem json log program_options regex thread)
    find_package (Boost CONFIG ${BV} REQUIRED COMPONENTS ${BOOLIB})
    set (LLPROD ${LLPROD} Boost::chrono Boost::date_time Boost::json Boost::program_options Boost::regex Boost::thread)
else ()
    set (BOOLIB atomic chrono container date_time filesystem json log program_options regex system thread)
    find_package (Boost CONFIG ${BV} REQUIRED COMPONENTS system ${BOOLIB})
    set (LLPROD ${LLPROD} Boost::chrono Boost::date_time Boost::json Boost::program_options Boost::regex Boost::system Boost::thread)
endif ()

set (LLALL ${LLALL} Boost::filesystem pthread)

if (${NJ} MATCHES "1")
else ()
    set (LLPROD ${LLPROD} Boost::json)
endif ()

if (DEFINED ENV{BOOST})
   # bbug in findboost means it fails to record location of libraries
   set (BOOST_LIBPATH $ENV{BOOST}/lib)
endif ()

message (DEBUG "Boost " ${Boost_VERSION_MAJOR}-${Boost_VERSION_MINOR} ", " ${Boost_INCLUDE_DIR} ", " ${Boost_INCLUDE_DIRS} ", " ${Boost_LIBRARY_DIRS}
                ", " ${Boost_LIBRARIES} ", " ${Boost_LIBRARY_DIR_RELEASE} ", " ${Boost_LIBRARY_DIR_DEBUG} ", " ${BOOST_LIBPATH} ".")

if (${NOICU} MATCHES "1")
  message (VERBOSE "No ICU")
else ()
    find_package (ICU 60.0 REQUIRED COMPONENTS dt in io tu uc)
    if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
        set (ICU_DEBUG ON)
    else ()
        set (ICU_DEBUG OFF)
    endif ()
    cmake_path (GET ICU_DT_LIBRARIES PARENT_PATH ICU_LIBRARY_DIR)
    message (DEBUG "ICU " ${ICU_VERSION} ", " ${ICU_INCLUDE_DIRS} ", " ${ICU_LIBRARIES}
                    ", " ${ICU_DT_LIBRARIES} ", " ${ICU_I18N_LIBRARIES} ", " ${ICU_IO_LIBRARIES} ", " ${ICU_TU_LIBRARIES} ", " ${ICU_UC_LIBRARIES} ", " ${ICU_LIBRARY_DIR} ".")
    set (LLPROD ${LLPROD} ${ICU_LIBRARIES})
    set (INC ${INC} ${ICU_INCLUDE_DIRS})
endif ()

find_package (Iconv REQUIRED)
message (DEBUG "Iconv " ${Iconv_VERSION} ", " ${Iconv_INCLUDE_DIRS} ", " ${Iconv_LIBRARIES})
set (INC ${INC} ${Iconv_INCLUDE_DIRS})
set (LLALL ${LLALL} "Iconv::Iconv")

if (${NOX} MATCHES "0")
  find_package (wxWidgets REQUIRED)
  include (${wxWidgets_USE_FILE})
  message (DEBUG "wxWidgets: " ${wxWidgets_INCLUDE_DIRS} ", " ${wxWidgets_LIBRARY_DIRS} ", " ${wxWidgets_LIBRARIES})
  set (LLGOOEY ${LLGOOEY} ${wxWidgets_LIBRARIES})
  set (INC ${INC} ${wxWidgets_INCLUDE_DIRS})
endif ()

if (DEFINED NO_GSL)
  message (VERBOSE "No GSL")
  set (CDEF_PROD ${CDEF_PROD} NO_GSL)
endif ()

if (DEFINED SIGNING)
  find_package (libreSSL REQUIRED)
  message (VERBOSE "libreSSL " ${LIBRESSL_VERSION})
  set (INC ${INC} ${LIBRESSL_INCLUDE_DIR})
  set (LLALL ${LLALL} ${LIBRESSL_CRYPTO_LIBRARY})
  set (CDEF_ALL ${CDEF_ALL} SIGNING)
endif ()

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
  message (VERBOSE "debug build")
  set (CDEF_ALL ${CDEF_ALL} _DEBUG)
  if (DEFINED SANITY)
    set (CLAUS "-g;-O0;-fvisibility=hidden;-fvisibility-inlines-hidden;-Wall;-Wextra;-Wno-dangling-else;-Wno-write-strings;-Wno-deprecated-declarations;-fsanitize=${SANITY}" ${IMPLICITFALL} ${NOINDENTLIE} ${TEMPLATEDEPTH})
    string (APPEND CMAKE_EXE_LINKER_FLAGS "-fsanitize=${SANITY}") 
  else ()
    set (CLAUS "-g;-O0;-fvisibility=hidden;-fvisibility-inlines-hidden;-Wall;-Wextra;-Wno-dangling-else;-Wno-write-strings;-Wno-deprecated-declarations" ${IMPLICITFALL} ${NOINDENTLIE} ${TEMPLATEDEPTH})
  endif ()
  set (TESCL "-g;-O0;-fvisibility=hidden;-fvisibility-inlines-hidden;-Wall;-Wextra;-Wno-dangling-else;-Wno-write-strings;-Wno-unused-result;-Wno-deprecated-declarations" ${IMPLICITFALL} ${NOINDENTLIE})
else ()
  message (VERBOSE "release build")
  set (CDEF_ALL ${CDEF_ALL} NDEBUG)
  set (CLAUS "-Os;-fvisibility=hidden;-fvisibility-inlines-hidden;-Wall;-Wextra;-Wno-dangling-else;-Wno-write-strings;-Wno-deprecated-declarations" ${IMPLICITFALL} ${NOINDENTLIE} ${TEMPLATEDEPTH})
  set (TESCL "-fvisibility=hidden;-fvisibility-inlines-hidden;-Wall;-Wextra;-Wno-dangling-else;-Wno-write-strings;-Wno-unused-result;-Wno-unused-parameter;-Wno-deprecated-declarations" ${IMPLICITFALL} ${NOINDENTLIE})
endif ()

if (${NS} MATCHES "1")
  message (NOTICE "No spelling")
  set (CDEF_ALL ${CDEF_ALL} NOSPELL)
else ()
  find_library (HUN NAMES "libhunspell-${HV}" "hunspell-${HV}" "libhunspell" "hunspell-${HV}" HINTS ${LB} PATH_SUFFIXES "/hunspell" DOC "hunspell-${HV}" REQUIRED)
  message (DEBUG "hunspell: " ${HUN})
  set (LLPROD ${LLPROD} ${HUN})
endif ()

link_directories (${LD})

add_executable (${XTEST} ${TOASTERS})
target_include_directories (${XTEST} PRIVATE ${H} ${INC})
target_compile_options (${XTEST} PRIVATE ${TESCL})
target_compile_definitions (${XTEST} PRIVATE OS_VER="${TARGET_OS}" ${ARCHITECTURE} ${CDEF_TEST} ${CDEF_ALL})
target_link_libraries (${XTEST} PRIVATE ${LLALL} ${LLTEST})

add_executable (${XSHELL} ${HEATERS} ${SAUCE})
target_include_directories (${XSHELL} PRIVATE ${H} ${INC})
target_precompile_headers (${XSHELL} PRIVATE ${H}/main/include.h)
target_compile_options (${XSHELL} PRIVATE ${CLAUS})
target_compile_definitions (${XSHELL} PRIVATE OS_VER="${TARGET_OS}" ${ARCHITECTURE} ${CDEF_SHELL} ${CDEF_PROD} ${CDEF_ALL})
target_link_libraries (${XSHELL} PRIVATE ${LLALL} ${LLSHELL} ${LLPROD})
install (TARGETS ${XSHELL} DESTINATION ${D})

install (FILES ${CMAKE_CURRENT_SOURCE_DIR}/README.txt ${CMAKE_CURRENT_SOURCE_DIR}/gen.txt ${CMAKE_CURRENT_SOURCE_DIR}/LICENCE.txt ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt ${CMAKE_CURRENT_SOURCE_DIR}/usage.txt DESTINATION ${DOCU})

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

    set (MACOSX_RPATH TRUE)

    add_executable (${XAPP} MACOSX_BUNDLE ${HEATERS} ${GOOEY} ${SAUCE})
    target_include_directories (${XAPP} PRIVATE ${H} ${INC})
    target_precompile_headers (${XAPP} PRIVATE ${H}/main/include.h)
    target_compile_options (${XAPP} PRIVATE ${CLAUS})
    target_compile_definitions (${XAPP} PRIVATE OS_VER="${TARGET_OS}" ${ARCHITECTURE} ${CDEF_WAX} ${CDEF_PROD} ${CDEF_ALL})
    target_link_libraries (${XAPP} PRIVATE ${LLALL} ${LLWAX} ${LLPROD} ${LLGOOEY})

    # layout inspired by the GIMP
    set (MCM ${MC}/MacOS)
    set (MCR ${MC}/Resources)
    set (MCI "Icon.icns")

    set_target_properties (${XAPP} PROPERTIES
        BUNDLE True
        MACOSX_BUNDLE                                  "TRUE"
        MACOSX_BUNDLE_NAME                             "${XAPP}"
        MACOSX_BUNDLE_GUI_IDENTIFIER                   "lu.ssc.ssc"
        MACOSX_BUNDLE_BUNDLE_NAME                      "${XAPP}"
        MACOSX_BUNDLE_BUNDLE_VERSION                   "${VER}"
        MACOSX_BUNDLE_ICON_FILE                        "${MCI}"
        MACOSX_BUNDLE_SHORT_VERSION_STRING             "${VER}"
        MACOSX_RPATH                                   "${MCM}"
        BUILD_RPATH                                    "${MCM}"
        XCODE_ATTRIBUTE_LD_RUNPATH_SEARCH_PATHS        "${MCM}"
        MACOSX_BUNDLE_INFO_PLIST                       "${I}/Info.plist.in"
    )

    install (DIRECTORY "${CMAKE_BINARY_DIR}/${XAPP2}" DESTINATION "/Applications") # almost certainly needs localising

    add_custom_command (TARGET ${XAPP} PRE_LINK
        COMMAND rm -rf ${R}/help.zip ${R}/help.htb
        COMMAND zip ${R}/help.zip ${HLP}/*
        COMMAND mv ${R}/help.zip ${R}/help.htb
        WORKING_DIRECTORY ${R}
        BYPRODUCTS ${R}/help.htb
    )

    message (DEBUG ${LLALL} ", " ${LLPROD} ", " ${LLWAX} ", " ${LLGOOEY})
 
    # can't use FILE (...), it screws up symlinks

    add_custom_command (TARGET ${XAPP} POST_BUILD
        COMMAND mkdir -p ${MCM} ${MCR}
        COMMAND cp -Lr ${R}/help.htb ${I}/${MCI} ${CMAKE_CURRENT_SOURCE_DIR}/README.txt ${CMAKE_CURRENT_SOURCE_DIR}/gen.txt ${CMAKE_CURRENT_SOURCE_DIR}/LICENCE.txt ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt ${CMAKE_CURRENT_SOURCE_DIR}/usage.txt ${MCR}
        COMMAND cp -Lr ${ICU_LIBRARY_DIR}/libicu*dylib ${wxWidgets_LIBRARY_DIRS}/libwx*.dylib ${BOOST_LIBPATH}/libboost*dylib ${Iconv_LIBRARIES} ${HUN} ${MCM}
    )

    # vaguely based upon https://gist.github.com/SamuelMarks
    add_custom_command(
            TARGET ${XAPP} POST_BUILD
            COMMAND install_name_tool
                    -rpath "${MCM}" '@executable_path/../MacOS'
                    "${MCM}/${XAPP}"
            WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
            COMMENT "Replace library search path from absolute to relative"
    )

elseif (${NOX} MATCHES "0")

    add_executable (${XWAX} ${HEATERS} ${GOOEY} ${SAUCE})
    target_include_directories (${XWAX} PRIVATE ${H} ${INC})
    target_precompile_headers (${XWAX} PRIVATE ${H}/main/include.h)
    target_compile_options (${XWAX} PRIVATE ${CLAUS})
    target_compile_definitions (${XWAX} PRIVATE OS_VER="${TARGET_OS}" ${ARCHITECTURE} ${CDEF_WAX} ${CDEF_PROD} ${CDEF_ALL})
    target_link_libraries (${XWAX} PRIVATE ${LLALL} ${LLWAX} ${LLPROD} ${LLGOOEY})
    install (TARGETS ${XWAX} DESTINATION ${D})

endif ()

# uninstall target ( https://gitlab.kitware.com/cmake/community/-/wikis/FAQ#can-i-do-make-uninstall-with-cmake )
if (NOT TARGET uninstall)
  configure_file (
    "${TEA}/cmake_uninstall.cmake.in"
    "${TEA}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)
  add_custom_target (uninstall
    COMMAND ${CMAKE_COMMAND} -P ${TEA}/cmake_uninstall.cmake)
endif()

enable_testing ()

add_test (NAME toasty_toast WORKING_DIRECTORY ${TEA} COMMAND ssc-test -d -i ${TT}/output.txt ${TT}/input.spec)
add_test (NAME toast WORKING_DIRECTORY ${TEA} COMMAND ssc-test -v -x ${CMAKE_CURRENT_BINARY_DIR}/ssc -f ${TT}/nix.lst)

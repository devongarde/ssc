cmake_minimum_required (VERSION 3.19)
cmake_policy (SET CMP0074 NEW)
project (ssc VERSION 0.1.41 DESCRIPTION "static site checker" LANGUAGES CXX HOMEPAGE_URL "https://ssc.lu")

set (CMAKE_CXX_STANDARD 17)

# expects standard ssc directory structure ...
set (R ${CMAKE_SOURCE_DIR}/recipe)
set (H ${R}/heater)
set (S ${R}/sauce)
set (T ${R}/toast)
set (TT ${T}/ssc-test)
set (TEA ${R}/tea)

# if using a non-thread safe version of SSL, add this compiler definition
# CURL_SSL_NOT_THREADSAFE

set (BV "1.75")

# Debug / Release (https://riptutorial.com/cmake/example/26702/setting-a-release-debug-configuration)
set (CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)

if (DEFINED CMAKE_BUILD_TYPE)
  set_property (CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES})
endif ()

set (${PROJ_NAME}_PATH_INSTALL ${D} CACHE PATH "This directory contains an installation path")
set (CMAKE_DEBUG_POSTFIX "d")

add_executable (ssc-test)
add_executable (ssc)

set (IMPLICITFALL ";-Wno-implicit-fallthrough")
set (NOINDENTLIE ";-Wno-misleading-indentation")
set (TEMPLATEDEPTH "")
set (BREGEX "regex")

set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_MULTI_THREADED ON)
set (Boost_USE_DEBUG_LIBS OFF)
set (Boost_USE_DEBUG_RUNTIME OFF)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  message (FATAL_ERROR "Use the included Visual Studio solutions to build under Windows (https://visualstudio.microsoft.com/downloads/)")
endif ()

  if (${CMAKE_SYSTEM_NAME} MATCHES "OpenBSD")
    set (DOCU "/usr/local/share/doc/ssc")
    set (D "/usr/local/bin")
    set (INC "/usr/local/include/" "/usr/local/include/hunspell")
    set (LD "/usr/local/lib")
    set (LIB "/usr/local/lib/libhunspell-1.7.a")
    target_compile_definitions (ssc-test PRIVATE UNIX NO_PCF_STR)
    set (OS ${CMAKE_SYSTEM})

    if (${CMAKE_SYSTEM} MATCHES "OpenBSD-6.8")
      set (LIB "/usr/local/lib/libhunspell-1.6.a")
      set (BV "1.67")
      target_compile_definitions (ssc PRIVATE UNIX OS_VER="${OS}" NO_PCF_STR NO_JSONIC HUNSPELL)
    elseif (${CMAKE_SYSTEM} MATCHES "OpenBSD-6.9")
      set (BV "1.67")
      target_compile_definitions (ssc PRIVATE UNIX OS_VER="${OS}" NO_PCF_STR NO_JSONIC HUNSPELL)
    elseif (${CMAKE_SYSTEM} MATCHES "OpenBSD-7.0")
      target_compile_definitions (ssc PRIVATE UNIX OS_VER="${OS}" NO_PCF_STR HUNSPELL)
    elseif (${CMAKE_SYSTEM} MATCHES "OpenBSD-7.1")
      target_compile_definitions (ssc PRIVATE UNIX OS_VER="${OS}" NO_PCF_STR HUNSPELL)
    elseif (${CMAKE_SYSTEM} MATCHES "OpenBSD-7.2")
      set (NO_CURL "1")
      target_compile_definitions (ssc PRIVATE UNIX OS_VER="${OS}" NO_PCF_STR NOCURL HUNSPELL)
    elseif (${CMAKE_SYSTEM} MATCHES "OpenBSD-7.3")
      set (NO_CURL "1")
      target_compile_definitions (ssc PRIVATE UNIX OS_VER="${OS}" NO_PCF_STR NOCURL HUNSPELL)
    else ()
      message (WARNING "untested version of OpenBSD")
      set (OS "OpenBSD?")
      target_compile_definitions (ssc PRIVATE UNIX OS_VER="${OS}" OMG NO_PCF_STR NO_JSONIC HUNSPELL)
    endif ()
  elseif (${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
    set (DOCU "/usr/local/share/doc/ssc")
    set (D "/usr/local/bin")
    set (INC "/usr/local/include/" "/usr/local/include/hunspell")
    set (LD "/usr/local/lib")
    set (LIB "/usr/local/lib/libhunspell-1.7.a")
    set (OS ${CMAKE_SYSTEM})
    target_compile_definitions (ssc-test PRIVATE UNIX NO_PCF_STR)
    set (NO_CURL "1")
    if (${CMAKE_SYSTEM} MATCHES "FreeBSD-13.1")
      target_compile_definitions (ssc PRIVATE UNIX OS_VER="${OS}" NO_PCF_STR HUNSPELL NOCURL)
    elseif (${CMAKE_SYSTEM} MATCHES "FreeBSD-12.3")
      target_compile_definitions (ssc PRIVATE UNIX OS_VER="${OS}" NO_PCF_STR HUNSPELL NOCURL)
    else ()
      set (OS "FreeBSD?")
      message (WARNING "untested version of FreeBSD")
      target_compile_definitions (ssc PRIVATE UNIX OS_VER="${OS}" OMG NO_PCF_STR NO_JSONIC HUNSPELL NOCURL)
    endif ()
  elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    if (DEFINED FLAVOUR)
      SET (LSB_RELEASE_ID_SHORT "${FLAVOUR}")
    elseif (DEFINED ENV{FLAVOUR})
      SET (LSB_RELEASE_ID_SHORT ENV{FLAVOUR})
    else ()
      find_program (LSB_RELEASE lsb_release)
      execute_process (COMMAND ${LSB_RELEASE} -is
        OUTPUT_VARIABLE LSB_RELEASE_ID_SHORT OUTPUT_STRIP_TRAILING_WHITESPACE)
    endif ()
    if (DEFINED FLAVOUR_VER)
      SET (LSB_RELEASE_VER_SHORT "${FLAVOUR_VER}")
    elseif (DEFINED ENV{FLAVOUR_VER})
      SET (LSB_RELEASE_VER_SHORT ENV{FLAVOUR_VER})
    else ()
      find_program (LSB_RELEASE lsb_release)
      execute_process (COMMAND ${LSB_RELEASE} -rs
        OUTPUT_VARIABLE LSB_RELEASE_VER_SHORT OUTPUT_STRIP_TRAILING_WHITESPACE)
    endif ()
    if ("${LSB_RELEASE_ID_SHORT}" STREQUAL "")
      set (OS "Linux")
      message (WARNING "Unknown flavour of Linux; please install lsb_release or specify FLAVOUR and FLAVOUR_VER")
      target_compile_definitions (ssc PRIVATE UNIX OS_VER="${OS}" OMG NO_JSONIC HUNSPELL BOOST_BIND_GLOBAL_PLACEHOLDERS)
      target_compile_definitions (ssc-test PRIVATE UNIX)
    else ()
      set (OS "${LSB_RELEASE_ID_SHORT} ${LSB_RELEASE_VER_SHORT}")
      target_compile_definitions (ssc PRIVATE UNIX OS_VER="${OS}" NO_JSONIC HUNSPELL BOOST_BIND_GLOBAL_PLACEHOLDERS)
      target_compile_definitions (ssc-test PRIVATE UNIX)
    endif ()
    set (BV "1.67")
    set (D "/usr/local/bin")
    set (DOCU "/usr/share/doc/ssc")
    set (INC "/usr/include/" "/usr/local/include/" "/usr/include/hunspell" "/usr/include/x86_64-linux-gnu/")
    set (LD "/usr/lib64/")
    set (LIB "/usr/lib64/libhunspell-1.7.so")
    set (Boost_USE_STATIC_LIBS OFF)
    if (${LSB_RELEASE_ID_SHORT} MATCHES "Ubuntu")
      set (LD "/usr/lib/x86_64-linux-gnu/")
      set (LIB "/usr/lib/x86_64-linux-gnu/libhunspell-1.7.so")
    elseif (${LSB_RELEASE_ID_SHORT} MATCHES "CentOSStream")
      if (${LSB_RELEASE_VER_SHORT} MATCHES "8")
        set (BV "1.66")
        set (LIB "/usr/lib64/libhunspell-1.6.so")
      endif ()
    endif ()
  elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set (D "/opt/local/bin")
    set (DOCU "/opt/local/share/doc")
    set (INC "/usr/local/include/" "/opt/local/include/" "/opt/local/include/hunspell")
    set (LD "/usr/local/lib" "/opt/local/lib")
    set (Boost_USE_STATIC_LIBS OFF)
    target_compile_definitions (ssc-test PRIVATE UNIX)
    if (${CMAKE_SYSTEM} MATCHES "Darwin-22")
      set (OS "Ventura")
      set (LIB "/opt/local/lib/libhunspell-1.7.a")
      target_compile_definitions (ssc PRIVATE OS_VER="${OS}" UNIX HUNSPELL CLEAN_SHAREDPTR_ARRAY ORDERED)
#      set (SANITY "address")
    elseif (${CMAKE_SYSTEM} MATCHES "Darwin-21")
      set (OS "Monterey")
      set (LIB "/opt/local/lib/libhunspell-1.7.a")
      target_compile_definitions (ssc PRIVATE OS_VER="${OS}" UNIX HUNSPELL CLEAN_SHAREDPTR_ARRAY)
    elseif (${CMAKE_SYSTEM} MATCHES "Darwin-20")
      set (OS "Big Sur")
      set (LIB "/opt/local/lib/libhunspell-1.7.a")
      target_compile_definitions (ssc PRIVATE OS_VER="${OS}" UNIX HUNSPELL)
    elseif (${CMAKE_SYSTEM} MATCHES "Darwin-19")
      set (LIB "/opt/local/lib/libhunspell-1.7.a")
      set (OS "Catalina")
      target_compile_definitions (ssc PRIVATE OS_VER="${OS}" UNIX NO_JSONIC HUNSPELL)
    elseif (${CMAKE_SYSTEM} MATCHES "Darwin-18")
      set (OS "Mojave")
      set (NOINDENTLIE "")
      target_compile_definitions (ssc PRIVATE OS_VER="${OS}" UNIX NO_JSONIC NOSPELL)
    elseif (${CMAKE_SYSTEM} MATCHES "Darwin-17")
      set (OS "High Sierra")
      set (NOINDENTLIE "")
      target_compile_definitions (ssc PRIVATE OS_VER="${OS}" UNIX FUDDYDUDDY NO_JSONIC NOSPELL NOMERGE)
    elseif (${CMAKE_SYSTEM} MATCHES "Darwin-16")
      set (OS "Sierra")
      set (NOINDENTLIE "")
      target_compile_definitions (ssc PRIVATE OS_VER="${OS}" UNIX FUDDYDUDDY NO_JSONIC NOSPELL NOMERGE NO_GSL)
    elseif (${CMAKE_SYSTEM} MATCHES "Darwin-15")
      set (OS "El Capitan")
      set (IMPLICITFALL "")
      set (NOINDENTLIE "")
      set (TEMPLATEDEPTH ";-ftemplate-depth=4096")
      target_compile_definitions (ssc PRIVATE OS_VER="${OS}" UNIX FUDDYDUDDY NO_JSONIC NOSPELL NOMERGE NO_GSL NO_FALLTHROUGH)
    elseif (${CMAKE_SYSTEM} MATCHES "Darwin-14")
      set (OS "Yosemite")
      set (IMPLICITFALL "")
      set (NOINDENTLIE "")
      set (TEMPLATEDEPTH ";-ftemplate-depth=4096")
      set (BREGEX "")
      target_compile_definitions (ssc PRIVATE OS_VER="${OS}" UNIX FUDDYDUDDY NO_JSONIC NOSPELL NOMERGE NO_GSL NO_FALLTHROUGH NO_BOOST_REGEX ELDERLY_CPP)
    elseif (${CMAKE_SYSTEM} MATCHES "Darwin-13")
      message (FATAL_ERROR "ssc requires a more recent C++ dialect than that available in Mavericks")
    elseif (${CMAKE_SYSTEM} MATCHES "Darwin-12")
      message (FATAL_ERROR "ssc requires a more recent C++ dialect than that available in Mountain Lion")
    elseif (${CMAKE_SYSTEM} MATCHES "Darwin-11")
      message (FATAL_ERROR "ssc requires a more recent C++ dialect than that available in Lion")
    elseif (${CMAKE_SYSTEM} MATCHES "Darwin-10")
      message (FATAL_ERROR "ssc requires a more recent C++ dialect than that available in Snow Leopard")
    elseif (${CMAKE_SYSTEM} MATCHES "Darwin-9")
      message (FATAL_ERROR "ssc requires a more recent C++ dialect than that available in Leopard")
    elseif (${CMAKE_SYSTEM} MATCHES "Darwin-8")
      message (FATAL_ERROR "ssc requires a more recent C++ dialect than that available in Tiger")
    elseif (${CMAKE_SYSTEM} MATCHES "Darwin-7")
      message (FATAL_ERROR "ssc requires a more recent C++ dialect than that available in Panther")
    elseif (${CMAKE_SYSTEM} MATCHES "Darwin-6")
      message (FATAL_ERROR "ssc requires a more recent C++ dialect than that available in Jaguar")
    else ()
      message (WARNING "unknown, untested MacOS")
      set (OS "Darwin?")
      target_compile_definitions (ssc PRIVATE OS_VER="${OS}" UNIX)
    endif ()
    find_program(DSYMUTIL_PROGRAM dsymutil)
    if (DSYMUTIL_PROGRAM)
      foreach(lang C CXX)
        foreach(var LINK_EXECUTABLE CREATE_SHARED_LIBRARY)
          set(CMAKE_${lang}_${var} "${CMAKE_${lang}_${var}}" "${DSYMUTIL_PROGRAM} <TARGET>")
        endforeach()
      endforeach()
    endif()
  else ()
    message (WARNING "unknown, untested, system: good luck")
    set (OS "unknown")
    set (D "~/bin")
    target_compile_definitions (ssc PRIVATE OS_VER="${OS}" OMG NO_JSONIC NOSPELL NO_PCF_STR)
  endif ()

target_link_libraries (ssc PRIVATE ${LIB})

message (${OS})

find_package (Boost ${BV} REQUIRED COMPONENTS system chrono date_time filesystem locale program_options thread ${BREGEX})
find_package (ICU 60.0 REQUIRED COMPONENTS dt in io tu uc)
find_package (Iconv REQUIRED)

# better to list the build files in one place (here) rather than litter all the source directories with a gadzillion untidy wee files
target_sources (ssc-test PRIVATE ${S}/test/ssc-test.cpp ${H}/main/version.h ${H}/feedback/nitnames.h ${S}/feedback/nitnames.cpp)
target_sources (ssc PRIVATE
        ${H}/attribute/attr.h ${H}/attribute/attr_state.h ${H}/attribute/attribute.h ${H}/attribute/attribute_classes.h ${H}/attribute/attributes.h
            ${H}/attribute/avm.h ${H}/attribute/avm_data.h ${H}/attribute/namespace.h
        ${H}/base/base.h ${H}/base/reldef.h ${H}/base/sz.h ${H}/base/type_base.h ${H}/base/type_case.h ${H}/base/type_core.h ${H}/base/type_master.h
        ${H}/compound/compound.h ${H}/compound/type_all_of.h ${H}/compound/type_one_of.h ${H}/compound/type_some_of.h ${H}/compound/type_compound.h
            ${H}/compound/type_compounded.h ${H}/compound/type_csses.h ${H}/compound/type_fn.h ${H}/compound/type_httpequivs.h
            ${H}/compound/type_jsonics.h ${H}/compound/type_langs.h ${H}/compound/type_maths.h ${H}/compound/type_measures.h
            ${H}/compound/type_microdatas.h ${H}/compound/type_microformats.h ${H}/compound/type_mimes.h ${H}/compound/type_numerics.h
            ${H}/compound/type_svgs.h ${H}/compound/type_sz.h ${H}/compound/type_van.h ${H}/compound/type_varied.h
        ${H}/coop/fred.h ${H}/coop/kew.h ${H}/coop/knickers.h ${H}/coop/lox.h ${H}/coop/tls.h
        ${H}/css/arguments.h ${H}/css/css.h ${H}/css/css_attribute.h ${H}/css/css_class.h ${H}/css/css_element.h ${H}/css/css_parse.h
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
            ${H}/main/output.h ${H}/main/standard.h ${H}/main/version.h
        ${H}/microdata/microdata_export.h ${H}/microdata/microdata_itemid.h ${H}/microdata/microdata_itemprop.h ${H}/microdata/microdata_itemscope.h
            ${H}/microdata/microdata_itemtype.h
        ${H}/microformat/connection.h ${H}/microformat/family.h ${H}/microformat/field.h ${H}/microformat/microformat.h
            ${H}/microformat/microformat_classes.h ${H}/microformat/microformat_constructor.h ${H}/microformat/microformat_export.h
            ${H}/microformat/microformat_export_rel.h ${H}/microformat/microformat_properties.h ${H}/microformat/microformats.h
            ${H}/microformat/microformats_ptr.h ${H}/microformat/prop.h ${H}/microformat/property.h ${H}/microformat/property_classes.h
            ${H}/microformat/property_value.h ${H}/microformat/sibling.h
        ${H}/ontology/jsonld.h ${H}/ontology/ontology_hierarchy.h ${H}/ontology/ontology_name.h ${H}/ontology/ontology_property.h ${H}/ontology/ontology_structure.h
            ${H}/ontology/ontology_type.h ${H}/ontology/ontology_version.h
        ${H}/parser/html_version.h ${H}/parser/jsonic.h ${H}/parser/parse_abb.h ${H}/parser/parse_attribute.h ${H}/parser/parse_attributes.h
            ${H}/parser/parse_brac_ket.h ${H}/parser/parse_bracs_ket.h ${H}/parser/parse_element.h ${H}/parser/parse_elements.h ${H}/parser/parse_ssi.h
            ${H}/parser/pattern.h ${H}/parser/text.h ${H}/parser/text-data.h ${H}/parser/xhtml_xml.h
        ${H}/rdf/rdf.h ${H}/rdf/rdfa_prop.h ${H}/rdf/rdfa_type.h
        ${H}/simple/simple.h ${H}/simple/type_autocomplete.h ${H}/simple/type_css.h ${H}/simple/type_currency.h
            ${H}/simple/type_httpequiv.h ${H}/simple/type_jsonic.h ${H}/simple/type_media.h ${H}/simple/type_metaname.h ${H}/simple/type_rdf.h
            ${H}/simple/type_reals.h ${H}/simple/type_relational.h ${H}/simple/type_time.h ${H}/simple/type_url.h ${H}/simple/type_basic.h
            ${H}/simple/type_id.h ${H}/simple/type_layout.h ${H}/simple/type_math.h ${H}/simple/type_measure.h ${H}/simple/type_microdata.h
            ${H}/simple/type_microformat.h ${H}/simple/type_misc.h ${H}/simple/type_numeric.h ${H}/simple/type_svg.h
        ${H}/spell/spell.h ${H}/spell/phrase.h
        ${H}/stats/stats.h ${H}/stats/stats0.h ${H}/stats/stats1.h ${H}/stats/stats2.h ${H}/stats/stats3.h ${H}/stats/stats4.h ${H}/stats/stats5.h
            ${H}/stats/stats_impl.h
        ${H}/symbol/nstr.h ${H}/symbol/symbol.h ${H}/symbol/symbol_entry.h ${H}/symbol/symbol_key.h ${H}/symbol/symbol_store.h ${H}/symbol/symbol_table.h
        ${H}/type/type.h ${H}/type/type_csp.h
        ${H}/url/curl.h ${H}/url/url.h ${H}/url/url_parameters.h ${H}/url/url_protocol.h ${H}/url/url_sanitise.h ${H}/url/url_scheme.h
            ${H}/url/url_schemes.h
        ${H}/utility/bigvector.h ${H}/utility/bitset.h ${H}/utility/byteorder.h ${H}/utility/cache.h ${H}/utility/common.h ${H}/utility/filesystem.h
            ${H}/utility/lexical.h ${H}/utility/quote.h ${H}/utility/tuple.h
        ${H}/webpage/corpus.h ${H}/webpage/crosslink.h ${H}/webpage/directory.h ${H}/webpage/external.h ${H}/webpage/fileindex.h ${H}/webpage/headers.h
            ${H}/webpage/id.h ${H}/webpage/page.h ${H}/webpage/q.h ${H}/webpage/root.h
        ${S}/attribute/attr.cpp ${S}/attribute/attr_state.cpp ${S}/attribute/attribute_constructor.cpp ${S}/attribute/attribute.cpp
            ${S}/attribute/attributes.cpp ${S}/attribute/avm.cpp ${S}/attribute/avm_data_a.cpp
            ${S}/attribute/avm_data_b.cpp ${S}/attribute/avm_data_c.cpp ${S}/attribute/avm_data_d.cpp ${S}/attribute/avm_data_e.cpp
            ${S}/attribute/avm_data_f1.cpp ${S}/attribute/avm_data_f2.cpp ${S}/attribute/avm_data_g.cpp ${S}/attribute/avm_data_h.cpp
            ${S}/attribute/avm_data_i.cpp ${S}/attribute/avm_data_k.cpp ${S}/attribute/avm_data_l.cpp ${S}/attribute/avm_data_m1.cpp
            ${S}/attribute/avm_data_m2.cpp ${S}/attribute/avm_data_n.cpp ${S}/attribute/avm_data_o.cpp ${S}/attribute/avm_data_p.cpp
            ${S}/attribute/avm_data_q.cpp ${S}/attribute/avm_data_r.cpp ${S}/attribute/avm_data_s.cpp ${S}/attribute/avm_data_t1.cpp
            ${S}/attribute/avm_data_t2.cpp ${S}/attribute/avm_data_u.cpp ${S}/attribute/avm_data_v.cpp ${S}/attribute/avm_data_w.cpp
            ${S}/attribute/avm_data_x.cpp ${S}/attribute/avm_data_rdf.cpp ${S}/attribute/namespace.cpp
        ${S}/base/type_base.cpp ${S}/base/type_case.cpp ${S}/base/type_core.cpp ${S}/base/type_master.cpp
        ${S}/coop/fred.cpp ${S}/coop/kew.cpp ${S}/coop/knickers.cpp ${S}/coop/lox.cpp
        ${S}/compound/type_csses.cpp ${S}/compound/type_varied.cpp
        ${S}/css/arguments.cpp ${S}/css/css.cpp ${S}/css/css_attribute.cpp ${S}/css/css_class.cpp ${S}/css/css_element.cpp ${S}/css/css_id.cpp
            ${S}/css/css_parse.cpp ${S}/css/css_state.cpp ${S}/css/decoration.cpp ${S}/css/descriptor.cpp  ${S}/css/descriptor_constructor.cpp
            ${S}/css/descriptors.cpp ${S}/css/distilled.cpp ${S}/css/ffv.cpp ${S}/css/ffvs.cpp ${S}/css/fn.cpp ${S}/css/global.cpp ${S}/css/group.cpp
            ${S}/css/media.cpp ${S}/css/medium.cpp ${S}/css/property.cpp ${S}/css/properties.cpp ${S}/css/property_constructor.cpp ${S}/css/rule.cpp
            ${S}/css/rules.cpp ${S}/css/selector.cpp ${S}/css/selectors.cpp ${S}/css/statement.cpp ${S}/css/statements.cpp ${S}/css/typed_property.cpp
            ${S}/css/value.cpp ${S}/css/value2.cpp ${S}/css/value_types_a.cpp ${S}/css/value_types_b_c.cpp ${S}/css/value_types_css_a.cpp 
            ${S}/css/value_types_css_b.cpp ${S}/css/value_types_css_c.cpp ${S}/css/value_types_css_d_e.cpp ${S}/css/value_types_css_f.cpp
            ${S}/css/value_types_css_g_l.cpp ${S}/css/value_types_css_m_p.cpp ${S}/css/value_types_css_r_s.cpp ${S}/css/value_types_css_t.cpp
            ${S}/css/value_types_css_u_z.cpp ${S}/css/value_types_c_e.cpp ${S}/css/value_types_f.cpp ${S}/css/value_types_g_i.cpp
            ${S}/css/value_types_j_l.cpp ${S}/css/value_types_m.cpp ${S}/css/value_types_n_o.cpp ${S}/css/value_types_p.cpp ${S}/css/value_types_q_r.cpp
            ${S}/css/value_types_s.cpp ${S}/css/value_types_t_u.cpp ${S}/css/value_types_v_z.cpp ${S}/css/weight.cpp 
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
        ${S}/main/abort.cpp ${S}/main/context.cpp ${S}/main/options.cpp ${S}/main/output.cpp ${S}/main/ssc.cpp ${S}/main/standard.cpp ${S}/main/version.cpp
        ${S}/microdata/microdata_export.cpp ${S}/microdata/microdata_itemid.cpp ${S}/microdata/microdata_itemprop.cpp ${S}/microdata/microdata_itemscope.cpp
            ${S}/microdata/microdata_itemtype.cpp
        ${S}/microformat/family.cpp ${S}/microformat/field.cpp ${S}/microformat/microformat_constructor.cpp ${S}/microformat/microformat_export.cpp
            ${S}/microformat/microformats.cpp ${S}/microformat/property_value.cpp ${S}/microformat/sibling.cpp
        ${S}/ontology/jsonld.cpp ${S}/ontology/ontology_hierarchy.cpp ${S}/ontology/ontology_name.cpp ${S}/ontology/ontology_property.cpp ${S}/ontology/ontology_structure.cpp
            ${S}/ontology/ontology_type.cpp ${S}/ontology/ontology_version.cpp
        ${S}/parser/html_version.cpp ${S}/parser/jsonic.cpp ${S}/parser/parse_attribute.cpp ${S}/parser/parse_attributes.cpp ${S}/parser/parse_brac_ket.cpp
            ${S}/parser/parse_bracs_ket.cpp ${S}/parser/parse_element.cpp ${S}/parser/parse_elements.cpp ${S}/parser/parse_ssi.cpp ${S}/parser/pattern.cpp
            ${S}/parser/text.cpp ${S}/parser/text-data.cpp ${S}/parser/xhtml_xml.cpp
        ${S}/rdf/rdf.cpp ${S}/rdf/rdfa_prop.cpp ${S}/rdf/rdfa_type.cpp
        ${S}/simple/type_autocomplete.cpp ${S}/simple/type_basic.cpp ${S}/simple/type_css.cpp
            ${S}/simple/type_currency.cpp ${S}/simple/type_d.cpp ${S}/simple/type_httpequiv.cpp ${S}/simple/type_id.cpp ${S}/simple/type_jsonic.cpp
            ${S}/simple/type_intent.cpp ${S}/simple/type_layout.cpp ${S}/base/type_master.cpp ${S}/simple/type_measure.cpp ${S}/simple/type_media.cpp
            ${S}/simple/type_metaname.cpp ${S}/simple/type_misc.cpp ${S}/simple/type_numeric.cpp ${S}/simple/type_paint.cpp
            ${S}/simple/type_rdf.cpp ${S}/simple/type_reals.cpp  ${S}/simple/type_sgml.cpp ${S}/simple/type_svg_feature.cpp
            ${S}/simple/type_time.cpp ${S}/simple/type_transform.cpp ${S}/compound/type_varied.cpp
        ${S}/spell/spell.cpp ${S}/spell/nixspell.cpp ${S}/spell/winspell.cpp
        ${S}/stats/stats.cpp ${S}/stats/stats_impl.cpp
        ${S}/symbol/nstr.cpp ${S}/symbol/symbol.cpp
        ${S}/type/type.cpp ${S}/type/type_csp.cpp
        ${S}/url/curl.cpp ${S}/url/url.cpp ${S}/url/url_parameters.cpp ${S}/url/url_protocol.cpp ${S}/url/url_sanitise.cpp ${S}/url/url_scheme.cpp
        ${S}/utility/byteorder.cpp ${S}/utility/cache.cpp ${S}/utility/common.cpp ${S}/utility/filesystem.cpp ${S}/utility/quote.cpp
        ${S}/webpage/corpus.cpp ${S}/webpage/crosslink.cpp ${S}/webpage/directory.cpp ${S}/webpage/external.cpp ${S}/webpage/fileindex.cpp
            ${S}/webpage/headers.cpp ${S}/webpage/id.cpp ${S}/webpage/page.cpp ${S}/webpage/q.cpp ${S}/webpage/root.cpp
)

target_precompile_headers (ssc PRIVATE ${H}/main/include.h)

target_include_directories (ssc-test PRIVATE ${H} ${INC})
target_include_directories (ssc PRIVATE ${H} ${INC})
link_directories (${LD})

target_compile_definitions (ssc-test PRIVATE SSC_TEST)

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
  message ("debug")
  target_compile_definitions (ssc-test PRIVATE _DEBUG)
  target_compile_definitions (ssc PRIVATE _DEBUG)
  target_compile_options (ssc-test PRIVATE "-g;-O0;-fvisibility=hidden;-fvisibility-inlines-hidden;-Wall;-Wextra;-Wno-dangling-else;-Wno-write-strings;-Wno-unused-result;-Wno-deprecated-declarations" ${IMPLICITFALL} ${NOINDENTLIE})
  if (DEFINED SANITY)
    target_compile_options (ssc PRIVATE "-g;-O0;-fvisibility=hidden;-fvisibility-inlines-hidden;-Wall;-Wextra;-Wno-dangling-else;-Wno-write-strings;-Wno-deprecated-declarations;-fsanitize=${SANITY}" ${IMPLICITFALL} ${NOINDENTLIE} ${TEMPLATEDEPTH})
    string (APPEND CMAKE_EXE_LINKER_FLAGS "-fsanitize=${SANITY}") 
  else ()
      target_compile_options (ssc PRIVATE "-g;-O0;-fvisibility=hidden;-fvisibility-inlines-hidden;-Wall;-Wextra;-Wno-dangling-else;-Wno-write-strings;-Wno-deprecated-declarations" ${IMPLICITFALL} ${NOINDENTLIE} ${TEMPLATEDEPTH})
  endif ()
else ()
  target_compile_definitions (ssc-test PRIVATE NDEBUG)
  target_compile_definitions (ssc PRIVATE NDEBUG)
  target_compile_options (ssc-test PRIVATE "-fvisibility=hidden;-fvisibility-inlines-hidden;-Wall;-Wextra;-Wno-dangling-else;-Wno-write-strings;-Wno-unused-result;-Wno-unused-parameter;-Wno-deprecated-declarations" ${IMPLICITFALL} ${NOINDENTLIE})
  target_compile_options (ssc PRIVATE "-Os;-fvisibility=hidden;-fvisibility-inlines-hidden;-Wall;-Wextra;-Wno-dangling-else;-Wno-write-strings;-Wno-unused-parameter;-Wno-deprecated-declarations" ${IMPLICITFALL} ${NOINDENTLIE} ${TEMPLATEDEPTH})
endif ()

target_link_libraries (ssc-test PRIVATE Boost::filesystem)
target_link_libraries (ssc-test PRIVATE pthread)

target_link_libraries (ssc PRIVATE Boost::system)
target_link_libraries (ssc PRIVATE Boost::date_time)
target_link_libraries (ssc PRIVATE Boost::filesystem)
target_link_libraries (ssc PRIVATE Boost::program_options)
target_link_libraries (ssc PRIVATE Boost::locale)
target_link_libraries (ssc PRIVATE Boost::chrono)
target_link_libraries (ssc PRIVATE Boost::thread)
target_link_libraries (ssc PRIVATE pthread)
target_link_libraries (ssc PRIVATE ${ICU_LIBRARIES})

if ("${NO_CURL}" STREQUAL "")
  target_link_libraries (ssc PRIVATE curl)       
endif ()

install (TARGETS ssc DESTINATION ${D})
install (FILES ${CMAKE_CURRENT_SOURCE_DIR}/README.txt ${CMAKE_CURRENT_SOURCE_DIR}/gen.txt ${CMAKE_CURRENT_SOURCE_DIR}/LICENCE.txt ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt ${CMAKE_CURRENT_SOURCE_DIR}/usage.txt DESTINATION ${DOCU})

enable_testing ()

add_test (NAME toasty_toast WORKING_DIRECTORY ${TEA} COMMAND ssc-test -d -i ${TT}/output.txt ${TT}/input.spec)
add_test (NAME toast WORKING_DIRECTORY ${TEA} COMMAND ssc-test -v -x ${CMAKE_CURRENT_BINARY_DIR}/ssc -f ${TT}/nix.lst)

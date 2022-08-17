cmake_minimum_required (VERSION 3.12)
cmake_policy (SET CMP0074 NEW)
project (ssc VERSION 0.0.134 LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED True)

# presumes stuff about ssc directory structure ... :-(
set (R ${CMAKE_CURRENT_SOURCE_DIR}/recipe)
set (H ${R}/heater)
set (TH ${R}/third)
set (S ${R}/sauce)
set (T ${R}/toast)
set (TT ${T}/ssc-test)

set (BV "1.75")

# Debug / Release (https://riptutorial.com/cmake/example/26702/setting-a-release-debug-configuration)
set (CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)

if (DEFINED CMAKE_BUILD_TYPE)
  set_property (CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES})
endif ()

if (DEFINED ENV{BOOST} AND NOT DEFINED ENV{BOOST_ROOT})
  set (BOOST_ROOT ${BOOST})
endif ()

set (${PROJ_NAME}_PATH_INSTALL ${D} CACHE PATH "This directory contains an installation path")
set (CMAKE_DEBUG_POSTFIX "d")

add_executable (ssc-test)
add_executable (ssc)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  message ("Only Visual Studios 2017/19/22 are known to build")
  target_compile_definitions (ssc PRIVATE WINDOWS)
  set (D ${R}/..)
endif ()

if (UNIX)
  # USE_OS_TZDB is for Howard Hinnant's date library
  target_compile_definitions (ssc-test PRIVATE UNIX USE_OS_TZDB)
  target_compile_definitions (ssc PRIVATE UNIX USE_OS_TZDB)

  set (Boost_USE_STATIC_LIBS ON)
  set (Boost_USE_MULTI_THREADED OFF)
  link_directories (${BOOST_LIBRARYDIR} ${ICU_ROOT})

  if (${CMAKE_SYSTEM_NAME} MATCHES "OpenBSD")

    set (HI "/usr/local/include/hunspell")
    set (HL "/usr/local/lib")

    if (${CMAKE_SYSTEM} MATCHES "OpenBSD-6.8")
      message ("OpenBSD 6.8")
      set (HV "hunspell-1.6.a")
      set (BV "1.67")
      target_compile_definitions (ssc-test PRIVATE NO_PCF_STR)
      target_compile_definitions (ssc PRIVATE OPENBSD O68 NO_PCF_STR NO_BOOST_PROCESS NO_JSONIC HUNSPELL USE_OS_TZDB)
    elseif (${CMAKE_SYSTEM} MATCHES "OpenBSD-6.9")
      message ("OpenBSD 6.9")
      set (HV "hunspell-1.7.a")
      set (BV "1.67")
      target_compile_definitions (ssc-test PRIVATE NO_PCF_STR)
      target_compile_definitions (ssc PRIVATE OPENBSD O69 NO_PCF_STR NO_BOOST_PROCESS NO_JSONIC HUNSPELL USE_OS_TZDB)
    elseif (${CMAKE_SYSTEM} MATCHES "OpenBSD-7.0")
      message ("OpenBSD 7.0")
      set (HV "hunspell-1.7.a")
      target_compile_definitions (ssc-test PRIVATE NO_PCF_STR)
      target_compile_definitions (ssc PRIVATE OPENBSD O70 NO_PCF_STR NO_BOOST_PROCESS HUNSPELL USE_OS_TZDB)
    elseif (${CMAKE_SYSTEM} MATCHES "OpenBSD-7.1")
      message ("OpenBSD 7.1")
      set (HV "hunspell-1.7.a")
      target_compile_definitions (ssc-test PRIVATE NO_PCF_STR)
      target_compile_definitions (ssc PRIVATE OPENBSD O71 NO_PCF_STR NO_BOOST_PROCESS HUNSPELL USE_OS_TZDB)
    else ()
      message ("unknown, untested version of OpenBSD")
      target_compile_definitions (ssc PRIVATE OPENBSD NO_PCF_STR NO_BOOST_PROCESS NO_JSONIC NOSPELL USE_OS_TZDB)
    endif ()
  elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message ("Linux: only built under Centos 8/9 amd64 and Ubuntu Server 20.04 amd64")
    set (Boost_NO_SYSTEM_PATHS ON) # Under Linux, CMake's boost detection is ropey. Build you own.
    target_compile_definitions (ssc PRIVATE LINUX NO_JSONIC HUNSPELL BOOST_BIND_GLOBAL_PLACEHOLDERS)
    if (DEFINED ENV{HUNSPELL_INCLUDE})
      set (HI $ENV{HUNSPELL_INCLUDE})
    else ()
      set (HI "/usr/local/include/hunspell")
    endif ()
    if (DEFINED ENV{HUNSPELL_LIB})
      set (HL $ENV{HUNSPELL_LIB})
    else ()
      set (HL "/usr/local/lib")
    endif ()
    if (DEFINED ENV{HUNSPELL_VERSION})
      set (HV $ENV{HUNSPELL_VERSION})
    else ()
      set (HV "hunspell-1.7.so")
    endif ()
  elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    if (DEFINED ENV{HUNSPELL_INCLUDE})
      set (HI $ENV{HUNSPELL_INCLUDE})
    else ()
      set (HI "/opt/local/include/hunspell")
    endif ()
    if (DEFINED ENV{HUNSPELL_LIB})
      set (HL $ENV{HUNSPELL_LIB})
    else ()
      set (HL "/opt/local/lib")
    endif ()
    if (DEFINED ENV{HUNSPELL_VERSION})
      set (HV $ENV{HUNSPELL_VERSION})
    else ()
      set (HV "hunspell-1.7.a")
    endif ()
    if (${CMAKE_SYSTEM} MATCHES "Darwin-21")
      message ("MacOS Monterey")
      target_compile_definitions (ssc PRIVATE MONTEREY MACOS HUNSPELL)
    elseif (${CMAKE_SYSTEM} MATCHES "Darwin-20")
      message ("MacOS Big Sur")
      target_compile_definitions (ssc PRIVATE BIG_SUR MACOS HUNSPELL)
    elseif (${CMAKE_SYSTEM} MATCHES "Darwin-19")
      set (BV "1.67")
      message ("MacOS Catalina")
      target_compile_definitions (ssc PRIVATE CATALINA MACOS NO_JSONIC HUNSPELL)
    elseif (${CMAKE_SYSTEM} MATCHES "Darwin-18")
      set (BV "1.67")
      message ("MacOS Mojave")
      target_compile_definitions (ssc PRIVATE MOJAVE MACOS NO_JSONIC NOSPELL)
    elseif (${CMAKE_SYSTEM} MATCHES "Darwin-17")
      set (BV "1.67")
      message ("MacOS High Sierra")
      target_compile_definitions (ssc-test PRIVATE FUDDYDUDDY)
      target_compile_definitions (ssc PRIVATE HIGH_SIERRA FUDDYDUDDY MACOS NO_JSONIC NOSPELL)
    else ()
      set (BV "1.67")
      message ("unknown, untested MacOS")
      target_compile_definitions (ssc PRIVATE MACOS FUDDYDUDDY NO_JSONIC NOSPELL)
    endif ()
  else ()
    message ("unknown, untested, system: good luck")
    target_compile_definitions (ssc PRIVATE NO_JSONIC NOSPELL NO_PCF_STR NO_BOOST_PROCESS)
  endif ()

  set (D "~/bin")
endif ()

find_package (Boost ${BV} REQUIRED COMPONENTS system chrono date_time filesystem locale program_options thread)
find_package (ICU 60.0 REQUIRED COMPONENTS dt in io tu uc)
find_package (Iconv REQUIRED)

# better to list the build files in one place (here) rather than litter all the source directories with a gadzillion untidy wee files
target_sources (ssc-test PRIVATE ${S}/test/ssc-test.cpp ${H}/main/version.h ${H}/feedback/nitnames.h ${S}/feedback/nitnames.cpp)
target_sources (ssc PRIVATE
        ${TH}/date/date.h ${TH}/date/tz.h ${TH}/date/tz_private.h
        ${H}/attribute/attr.h ${H}/attribute/attribute.h ${H}/attribute/attribute_classes.h ${H}/attribute/attributes.h ${H}/attribute/avm.h
            ${H}/attribute/avm_data.h ${H}/attribute/namespace.h
        ${H}/coop/fred.h ${H}/coop/kew.h ${H}/coop/knickers.h ${H}/coop/lox.h ${H}/coop/tls.h
        ${H}/css/css.h ${H}/css/css_global.h ${H}/css/css_group.h
        ${H}/element/elem.h ${H}/element/element.h ${H}/element/element_attribute.h ${H}/element/element_classes.h ${H}/element/parentage.h
            ${H}/element/state.h
        ${H}/feedback/nit.h ${H}/feedback/nitnames.h ${H}/feedback/nitout.h ${H}/feedback/nitpick.h
        ${H}/icu/charset.h ${H}/icu/converter.h ${H}/icu/lingo.h ${H}/icu/wrapper.h
        ${H}/main/abort.h ${H}/main/args.h ${H}/main/context.h ${H}/main/include.h ${H}/main/options.h ${H}/main/output.h ${H}/main/standard.h
            ${H}/main/version.h
        ${H}/microdata/microdata_export.h ${H}/microdata/microdata_itemid.h ${H}/microdata/microdata_itemprop.h ${H}/microdata/microdata_itemscope.h
            ${H}/microdata/microdata_itemtype.h
        ${H}/microformat/connection.h ${H}/microformat/family.h ${H}/microformat/field.h ${H}/microformat/microformat.h
            ${H}/microformat/microformat_classes.h ${H}/microformat/microformat_constructor.h ${H}/microformat/microformat_export.h
            ${H}/microformat/microformat_export_rel.h ${H}/microformat/microformat_properties.h ${H}/microformat/microformats.h
            ${H}/microformat/microformats_ptr.h ${H}/microformat/prop.h ${H}/microformat/property.h ${H}/microformat/property_classes.h
            ${H}/microformat/property_value.h ${H}/microformat/sibling.h
        ${H}/parser/html_version.h ${H}/parser/jsonic.h ${H}/parser/parse_abb.h ${H}/parser/parse_attribute.h ${H}/parser/parse_attributes.h
            ${H}/parser/parse_bra_ket.h ${H}/parser/parse_bras_ket.h ${H}/parser/parse_css.h ${H}/parser/parse_element.h ${H}/parser/parse_elements.h
            ${H}/parser/parse_ssi.h ${H}/parser/pattern.h ${H}/parser/text.h ${H}/parser/text-data.h ${H}/parser/xhtml_xml.h
        ${H}/rdf/rdf.h ${H}/rdf/rdfa_prop.h ${H}/rdf/rdfa_type.h
        ${H}/schema/jsonld.h ${H}/schema/schema_hierarchy.h ${H}/schema/schema_name.h ${H}/schema/schema_property.h ${H}/schema/schema_structure.h
            ${H}/schema/schema_type.h ${H}/schema/schema_version.h
        ${H}/spell/spell.h ${H}/spell/phrase.h
        ${H}/stats/stats.h ${H}/stats/stats0.h ${H}/stats/stats1.h ${H}/stats/stats2.h ${H}/stats/stats3.h ${H}/stats/stats4.h ${H}/stats/stats_impl.h
        ${H}/symbol/nstr.h ${H}/symbol/symbol.h ${H}/symbol/symbol_entry.h ${H}/symbol/symbol_key.h ${H}/symbol/symbol_store.h ${H}/symbol/symbol_table.h
        ${H}/type/enum.h ${H}/type/reldef.h ${H}/type/sz.h ${H}/type/type.h ${H}/type/type_1.h ${H}/type/type_2.h ${H}/type/type_3.h ${H}/type/type_4.h
            ${H}/type/type_aria.h ${H}/type/type_autocomplete.h ${H}/type/type_base.h ${H}/type/type_case.h ${H}/type/type_charset.h ${H}/type/type_class.h
            ${H}/type/type_colour.h ${H}/type/type_cookie.h ${H}/type/type_core.h ${H}/type/type_country.h ${H}/type/type_csp.h ${H}/type/type_currency.h
            ${H}/type/type_enum.h ${H}/type/type_enum_vec.h ${H}/type/type_httpequiv.h ${H}/type/type_jsonic.h ${H}/type/type_lang.h ${H}/type/type_master.h
            ${H}/type/type_media.h ${H}/type/type_metaname.h ${H}/type/type_mime.h ${H}/type/type_rdf.h ${H}/type/type_reals.h ${H}/type/type_rel.h
            ${H}/type/type_relational.h ${H}/type/type_time.h ${H}/type/type_url.h ${H}/type/type_van.h ${H}/type/type_basic.h ${H}/type/type_id.h
            ${H}/type/type_layout.h ${H}/type/type_math.h ${H}/type/type_measure.h ${H}/type/type_microdata.h ${H}/type/type_microformat.h
            ${H}/type/type_misc.h ${H}/type/type_numeric.h ${H}/type/type_svg.h ${H}/type/type_varied.h ${H}/type/type_xmlns.h
        ${H}/url/url.h ${H}/url/url_parameters.h ${H}/url/url_protocol.h ${H}/url/url_sanitise.h ${H}/url/url_scheme.h ${H}/url/url_schemes.h
        ${H}/utility/bigvector.h ${H}/utility/byteorder.h ${H}/utility/cache.h ${H}/utility/common.h ${H}/utility/filesystem.h ${H}/utility/lexical.h
            ${H}/utility/quote.h ${H}/utility/tuple.h
        ${H}/webpage/corpus.h ${H}/webpage/crosslink.h ${H}/webpage/directory.h ${H}/webpage/external.h ${H}/webpage/fileindex.h ${H}/webpage/headers.h
            ${H}/webpage/id.h ${H}/webpage/page.h ${H}/webpage/q.h ${H}/webpage/root.h
        ${TH}/date/tz.cpp
        ${S}/attribute/attr.cpp ${S}/attribute/attribute_constructor.cpp ${S}/attribute/attributes.cpp ${S}/attribute/avm.cpp ${S}/attribute/avm_data_a.cpp
             ${S}/attribute/avm_data_b.cpp ${S}/attribute/avm_data_c.cpp ${S}/attribute/avm_data_d.cpp ${S}/attribute/avm_data_e.cpp
             ${S}/attribute/avm_data_f1.cpp ${S}/attribute/avm_data_f2.cpp ${S}/attribute/avm_data_g.cpp ${S}/attribute/avm_data_h.cpp
             ${S}/attribute/avm_data_i.cpp ${S}/attribute/avm_data_k.cpp ${S}/attribute/avm_data_l.cpp ${S}/attribute/avm_data_m1.cpp
             ${S}/attribute/avm_data_m2.cpp ${S}/attribute/avm_data_n.cpp ${S}/attribute/avm_data_o.cpp ${S}/attribute/avm_data_p.cpp
             ${S}/attribute/avm_data_q.cpp ${S}/attribute/avm_data_r.cpp ${S}/attribute/avm_data_s.cpp ${S}/attribute/avm_data_t1.cpp
             ${S}/attribute/avm_data_t2.cpp ${S}/attribute/avm_data_u.cpp ${S}/attribute/avm_data_v.cpp ${S}/attribute/avm_data_w.cpp
             ${S}/attribute/avm_data_x.cpp ${S}/attribute/avm_data_rdf.cpp ${S}/attribute/namespace.cpp
        ${S}/coop/fred.cpp ${S}/coop/kew.cpp ${S}/coop/knickers.cpp ${S}/coop/lox.cpp
        ${S}/css/css.cpp ${S}/css/css_global.cpp ${S}/css/css_group.cpp
        ${S}/element/elem.cpp ${S}/element/element.cpp ${S}/element/element_abcd.cpp ${S}/element/element_aria.cpp ${S}/element/element_attributes.cpp
            ${S}/element/element_classes.cpp ${S}/element/element_efghi.cpp ${S}/element/element_examine.cpp ${S}/element/element_input.cpp
            ${S}/element/element_jkl.cpp ${S}/element/element_microdata.cpp ${S}/element/element_microformats.cpp ${S}/element/element_mno.cpp
            ${S}/element/element_pqr.cpp ${S}/element/element_rdfa.cpp ${S}/element/element_s.cpp ${S}/element/element_tuvwxyz.cpp ${S}/element/parentage.cpp
            ${S}/element/state.cpp
        ${S}/feedback/nit.cpp ${S}/feedback/nitnames.cpp ${S}/feedback/nitout.cpp ${S}/feedback/nitpick.cpp
        ${S}/icu/charset.cpp ${S}/icu/converter.cpp ${S}/icu/lingo.cpp ${S}/icu/wrapper.cpp
        ${S}/main/abort.cpp ${S}/main/context.cpp ${S}/main/options.cpp ${S}/main/output.cpp ${S}/main/ssc.cpp ${S}/main/standard.cpp ${S}/main/version.cpp
        ${S}/microdata/microdata_export.cpp ${S}/microdata/microdata_itemid.cpp ${S}/microdata/microdata_itemprop.cpp ${S}/microdata/microdata_itemscope.cpp
            ${S}/microdata/microdata_itemtype.cpp
        ${S}/microformat/family.cpp ${S}/microformat/field.cpp ${S}/microformat/microformat_constructor.cpp ${S}/microformat/microformat_export.cpp
            ${S}/microformat/microformats.cpp ${S}/microformat/property_value.cpp ${S}/microformat/sibling.cpp
        ${S}/parser/html_version.cpp ${S}/parser/jsonic.cpp ${S}/parser/parse_attribute.cpp ${S}/parser/parse_attributes.cpp ${S}/parser/parse_bra_ket.cpp
            ${S}/parser/parse_bras_ket.cpp ${S}/parser/parse_css.cpp ${S}/parser/parse_element.cpp ${S}/parser/parse_elements.cpp ${S}/parser/parse_ssi.cpp
            ${S}/parser/pattern.cpp ${S}/parser/text.cpp ${S}/parser/text-data.cpp ${S}/parser/xhtml_xml.cpp
        ${S}/rdf/rdf.cpp ${S}/rdf/rdfa_prop.cpp ${S}/rdf/rdfa_type.cpp
        ${S}/schema/jsonld.cpp ${S}/schema/schema_hierarchy.cpp ${S}/schema/schema_name.cpp ${S}/schema/schema_property.cpp ${S}/schema/schema_structure.cpp
            ${S}/schema/schema_type.cpp ${S}/schema/schema_version.cpp
        ${S}/spell/spell.cpp ${S}/spell/nixspell.cpp ${S}/spell/winspell.cpp
        ${S}/stats/stats.cpp ${S}/stats/stats_impl.cpp
        ${S}/symbol/nstr.cpp ${S}/symbol/symbol.cpp
        ${S}/type/type.cpp ${S}/type/type_aria.cpp ${S}/type/type_autocomplete.cpp ${S}/type/type_charset.cpp ${S}/type/type_class.cpp ${S}/type/type_colour.cpp
            ${S}/type/type_core.cpp ${S}/type/type_country.cpp ${S}/type/type_csp.cpp ${S}/type/type_currency.cpp ${S}/type/type_d.cpp ${S}/type/type_enum.cpp
            ${S}/type/type_httpequiv.cpp ${S}/type/type_intent.cpp ${S}/type/type_lang.cpp ${S}/type/type_media.cpp ${S}/type/type_metaname.cpp
            ${S}/type/type_mime.cpp ${S}/type/type_numeric.cpp ${S}/type/type_paint.cpp ${S}/type/type_rdf.cpp ${S}/type/type_reals.cpp ${S}/type/type_rel.cpp
            ${S}/type/type_sgml.cpp ${S}/type/type_svg_feature.cpp ${S}/type/type_time.cpp ${S}/type/type_transform.cpp ${S}/type/type_url.cpp
            ${S}/type/type_varied.cpp ${S}/type/type_xmlns.cpp
        ${S}/url/url.cpp ${S}/url/url_parameters.cpp ${S}/url/url_protocol.cpp ${S}/url/url_sanitise.cpp ${S}/url/url_scheme.cpp
        ${S}/utility/byteorder.cpp ${S}/utility/cache.cpp ${S}/utility/common.cpp ${S}/utility/filesystem.cpp ${S}/utility/quote.cpp
        ${S}/webpage/corpus.cpp ${S}/webpage/crosslink.cpp ${S}/webpage/directory.cpp ${S}/webpage/external.cpp ${S}/webpage/fileindex.cpp
            ${S}/webpage/headers.cpp ${S}/webpage/id.cpp ${S}/webpage/page.cpp ${S}/webpage/q.cpp ${S}/webpage/root.cpp
)

target_include_directories (ssc-test PRIVATE ${H} ${BOOST_INCLUDE_DIR} $ENV{GSL}/include)
target_include_directories (ssc PRIVATE ${H} ${TH} ${BOOST_INCLUDE_DIR} ${ICU_INCLUDE_DIRS} $ENV{GSL}/include ${HI})

target_compile_definitions (ssc-test PRIVATE SSC_TEST)

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
  message ("debug")
  target_compile_definitions (ssc-test PRIVATE _DEBUG)
  target_compile_definitions (ssc PRIVATE _DEBUG)
  target_compile_options (ssc-test PRIVATE "-g;-O0;-fvisibility=hidden;-fvisibility-inlines-hidden;-Wall;-Wextra;-Wno-dangling-else;-Wno-write-strings;-Wno-implicit-fallthrough;-Wno-misleading-indentation;-Wno-unused-result;-Wno-deprecated-declarations")
  target_compile_options (ssc PRIVATE "-g;-O0;-fvisibility=hidden;-fvisibility-inlines-hidden;-Wall;-Wextra;-Wno-dangling-else;-Wno-write-strings;-Wno-implicit-fallthrough;-Wno-misleading-indentation;-Wno-deprecated-declarations")
else ()
  message ("release")
  target_compile_definitions (ssc-test PRIVATE NDEBUG)
  target_compile_definitions (ssc PRIVATE NDEBUG)
  if (${CMAKE_BUILD_TYPE} MATCHES "MinSizeRel")
    target_compile_options (ssc-test PRIVATE "-Os;-fvisibility=hidden;-fvisibility-inlines-hidden;-Wall;-Wextra;-Wno-dangling-else;-Wno-write-strings;-Wno-implicit-fallthrough;-Wno-misleading-indentation;-Wno-unused-result;-Wno-unused-parameter;-Wno-deprecated-declarations")
    target_compile_options (ssc PRIVATE "-Os;-fvisibility=hidden;-fvisibility-inlines-hidden;-Wall;-Wextra;-Wno-dangling-else;-Wno-write-strings;-Wno-implicit-fallthrough;-Wno-misleading-indentation;-Wno-unused-parameter;-Wno-deprecated-declarations")
  else ()
    target_compile_options (ssc-test PRIVATE "-O3;-fvisibility=hidden;-fvisibility-inlines-hidden;-Wall;-Wextra;-Wno-dangling-else;-Wno-write-strings;-Wno-implicit-fallthrough;-Wno-misleading-indentation;-Wno-unused-result;-Wno-unused-parameter;-Wno-deprecated-declarations")
    target_compile_options (ssc PRIVATE "-O3;-fvisibility=hidden;-fvisibility-inlines-hidden;-Wall;-Wextra;-Wno-dangling-else;-Wno-write-strings;-Wno-implicit-fallthrough;-Wno-misleading-indentation;-Wno-unused-parameter;-Wno-deprecated-declarations")
  endif ()
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

if (UNIX)
  target_link_libraries (ssc PRIVATE ${HL}/lib${HV})
endif ()

install (TARGETS ssc-test DESTINATION ${D})
install (TARGETS ssc DESTINATION ${D})

enable_testing ()

add_test (NAME toasty_toast COMMAND ssc-test -d -i ${TT}/output.txt ${TT}/input.spec)
add_test (NAME toast COMMAND ssc-test -v -x ${CMAKE_CURRENT_SOURCE_DIR}/ssc -f ${TT}/ssc.lst)

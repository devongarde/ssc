cmake_minimum_required (VERSION 3.11)
project (ssc VERSION 0.0.70 LANGUAGES CXX)

set (BOOST_ROOT ${BOOST})
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED True)

# presumes stuff about ssc directory structure ... :-(
set (R ${CMAKE_CURRENT_SOURCE_DIR}/..)
set (D ${R}/..)
set (H ${R}/heater)
set (S ${R}/sauce)
set (T ${R}/toast)
set (TT ${T}/ssc-test)

# Debug / Release (https://riptutorial.com/cmake/example/26702/setting-a-release-debug-configuration)
set (CMAKE_CONFIGURATION_TYPES "Debug;Release;MinSizeRel" CACHE STRING "Configs" FORCE)
if (DEFINED CMAKE_BUILD_TYPE)
  set_property (CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES})
endif ()
set (${PROJ_NAME}_PATH_INSTALL ${D} CACHE PATH "This directory contains an installation path")
set (CMAKE_DEBUG_POSTFIX "d")

set (Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.67 REQUIRED COMPONENTS date_time filesystem program_options)

add_executable (ssc-test)
add_executable (ssc)

# better to litter in one place (here) than in the source directories with an extra gadzillion files
target_sources (ssc-test PRIVATE ${S}/test/ssc-test.cpp ${H}/main/version.h ${H}/feedback/nitnames.h)
target_sources (ssc PRIVATE
    ${H}/attribute/attr.h ${H}/attribute/attribute.h ${H}/attribute/attribute_classes.h ${H}/attribute/attributes.h ${H}/attribute/avm.h ${H}/css/css.h ${H}/css/css_cache.h
    ${H}/element/elem.h ${H}/element/element.h ${H}/element/element_attribute.h ${H}/element/element_classes.h ${H}/element/parentage.h ${H}/element/state.h ${H}/feedback/nit.h
    ${H}/feedback/nitnames.h ${H}/feedback/nitpick.h ${H}/main/args.h ${H}/main/context.h ${H}/main/include.h ${H}/main/options.h ${H}/main/standard.h ${H}/main/version.h
    ${H}/microdata/microdata_export.h ${H}/microdata/microdata_itemid.h ${H}/microdata/microdata_itemprop.h ${H}/microdata/microdata_itemscope.h ${H}/microdata/microdata_itemtype.h
    ${H}/microformat/connection.h ${H}/microformat/family.h ${H}/microformat/field.h ${H}/microformat/microformat.h ${H}/microformat/microformat_classes.h
    ${H}/microformat/microformat_constructor.h ${H}/microformat/microformat_export.h ${H}/microformat/microformat_export_rel.h ${H}/microformat/microformat_properties.h
    ${H}/microformat/microformats.h ${H}/microformat/microformats_ptr.h ${H}/microformat/prop.h ${H}/microformat/property.h ${H}/microformat/property_classes.h
    ${H}/microformat/property_value.h ${H}/microformat/sibling.h ${H}/parser/html_version.h ${H}/parser/parse_attribute.h ${H}/parser/parse_attributes.h ${H}/parser/parse_bra_ket.h
    ${H}/parser/parse_bras_ket.h ${H}/parser/parse_css.h ${H}/parser/parse_element.h ${H}/parser/parse_elements.h ${H}/parser/parse_ssi.h ${H}/parser/text.h
    ${H}/parser/xhtml_xml.h ${H}/schema/schema_hierarchy.h ${H}/schema/schema_property.h ${H}/schema/schema_structure.h ${H}/schema/schema_type.h ${H}/schema/schema_version.h
    ${H}/stats/stats.h ${H}/stats/stats0.h ${H}/stats/stats1.h ${H}/stats/stats2.h ${H}/stats/stats_impl.h ${H}/symbol/symbol.h ${H}/symbol/symbol_table.h
    ${H}/type/enum.h ${H}/type/reldef.h ${H}/type/sz.h ${H}/type/type.h ${H}/type/type_1.h ${H}/type/type_2.h ${H}/type/type_3.h ${H}/type/type_4.h
    ${H}/type/type_aria.h ${H}/type/type_autocomplete.h ${H}/type/type_base.h ${H}/type/type_class.h ${H}/type/type_colour.h ${H}/type/type_core.h ${H}/type/type_currency.h
    ${H}/type/type_enum.h ${H}/type/type_enum_vec.h ${H}/type/type_httpequiv.h ${H}/type/type_lang.h ${H}/type/type_master.h ${H}/type/type_media.h ${H}/type/type_mime.h
    ${H}/type/type_rdf.h ${H}/type/type_reals.h ${H}/type/type_rel.h ${H}/type/type_relational.h ${H}/type/type_time.h ${H}/type/type_url.h ${H}/type/type_van.h
    ${H}/type/type_basic.h ${H}/type/type_id.h ${H}/type/type_layout.h ${H}/type/type_math.h ${H}/type/type_measure.h ${H}/type/type_microdata.h ${H}/type/type_microformat.h
    ${H}/type/type_misc.h ${H}/type/type_numeric.h ${H}/type/type_svg.h
    ${H}/type/type_varied.h ${H}/type/type_xmlns.h ${H}/url/url.h ${H}/url/url_parameters.h ${H}/url/url_protocol.h ${H}/url/url_sanitise.h ${H}/url/url_scheme.h
    ${H}/url/url_schemes.h ${H}/utility/bigvector.h ${H}/utility/byteorder.h ${H}/utility/common.h ${H}/utility/lexical.h ${H}/utility/quote.h ${H}/utility/tuple.h
    ${H}/webmention/hook.h ${H}/webmention/irt.h ${H}/webmention/webmention.h ${H}/webmention/webmentions.h ${H}/webpage/crosslink.h ${H}/webpage/directory.h
    ${H}/webpage/external.h ${H}/webpage/fileindex.h ${H}/webpage/headers.h ${H}/webpage/id.h ${H}/webpage/page.h ${H}/webpage/root.h ${S}/attribute/attr.cpp
    ${S}/attribute/attribute_constructor.cpp ${S}/attribute/attributes.cpp ${S}/attribute/avm.cpp ${S}/css/css.cpp ${S}/css/css_cache.cpp ${S}/element/elem.cpp
    ${S}/element/element.cpp ${S}/element/element_abcd.cpp ${S}/element/element_attributes.cpp ${S}/element/element_classes.cpp ${S}/element/element_efghi.cpp
    ${S}/element/element_examine.cpp ${S}/element/element_input.cpp ${S}/element/element_jkl.cpp ${S}/element/element_microdata.cpp ${S}/element/element_microformats.cpp
    ${S}/element/element_mno.cpp ${S}/element/element_pqr.cpp ${S}/element/element_s.cpp ${S}/element/element_tuvwxyz.cpp ${S}/element/parentage.cpp ${S}/element/state.cpp
    ${S}/feedback/nit.cpp ${S}/feedback/nitpick.cpp ${S}/main/context.cpp ${S}/main/options.cpp ${S}/main/ssc.cpp ${S}/main/standard.cpp ${S}/microdata/microdata_export.cpp
    ${S}/microdata/microdata_itemid.cpp ${S}/microdata/microdata_itemprop.cpp ${S}/microdata/microdata_itemscope.cpp ${S}/microdata/microdata_itemtype.cpp ${S}/microformat/family.cpp
    ${S}/microformat/field.cpp ${S}/microformat/microformat_constructor.cpp ${S}/microformat/microformat_export.cpp ${S}/microformat/microformats.cpp ${S}/microformat/property_value.cpp
    ${S}/microformat/sibling.cpp ${S}/parser/html_version.cpp ${S}/parser/parse_attribute.cpp ${S}/parser/parse_attributes.cpp ${S}/parser/parse_bra_ket.cpp ${S}/parser/parse_bras_ket.cpp
    ${S}/parser/parse_css.cpp ${S}/parser/parse_element.cpp ${S}/parser/parse_elements.cpp ${S}/parser/parse_ssi.cpp ${S}/parser/text.cpp ${S}/parser/xhtml_xml.cpp
    ${S}/schema/schema_hierarchy.cpp ${S}/schema/schema_property.cpp ${S}/schema/schema_structure.cpp ${S}/schema/schema_type.cpp ${S}/schema/schema_version.cpp ${S}/stats/stats.cpp
    ${S}/stats/stats_impl.cpp ${S}/symbol/symbol.cpp ${S}/symbol/symbol_table.cpp ${S}/type/type.cpp ${S}/type/type_aria.cpp ${S}/type/type_autocomplete.cpp ${S}/type/type_charset.cpp
    ${S}/type/type_class.cpp ${S}/type/type_colour.cpp ${S}/type/type_core.cpp ${S}/type/type_currency.cpp ${S}/type/type_d.cpp ${S}/type/type_enum.cpp ${S}/type/type_httpequiv.cpp
    ${S}/type/type_lang.cpp ${S}/type/type_media.cpp ${S}/type/type_metaname.cpp ${S}/type/type_mime.cpp ${S}/type/type_paint.cpp ${S}/type/type_reals.cpp ${S}/type/type_rel.cpp
    ${S}/type/type_sgml.cpp ${S}/type/type_svg_feature.cpp ${S}/type/type_time.cpp ${S}/type/type_transform.cpp ${S}/type/type_url.cpp ${S}/type/type_xmlns.cpp ${S}/url/url.cpp
    ${S}/url/url_parameters.cpp ${S}/url/url_protocol.cpp ${S}/url/url_sanitise.cpp ${S}/url/url_scheme.cpp ${S}/utility/byteorder.cpp ${S}/utility/common.cpp ${S}/utility/quote.cpp
    ${S}/webmention/hook.cpp ${S}/webmention/irt.cpp ${S}/webmention/webmention.cpp ${S}/webmention/webmentions.cpp ${S}/webpage/crosslink.cpp ${S}/webpage/directory.cpp
    ${S}/webpage/external.cpp ${S}/webpage/fileindex.cpp ${S}/webpage/headers.cpp ${S}/webpage/id.cpp ${S}/webpage/page.cpp ${S}/webpage/root.cpp
)

target_include_directories (ssc-test PRIVATE ${H} ${BOOST})
target_include_directories (ssc PRIVATE ${H} ${BOOST})

target_compile_options (ssc-test PRIVATE "-fvisibility=hidden;-fvisibility-inlines-hidden;-Wall;-Wextra;-Wno-dangling-else;-Wno-write-strings;-Wno-unused-parameter")
target_compile_options (ssc PRIVATE "-fvisibility=hidden;-fvisibility-inlines-hidden;-Wall;-Wextra;-Wno-dangling-else;-Wno-write-strings;-Wno-unused-parameter")

target_compile_definitions (ssc-test PRIVATE SSC_TEST)

if (UNIX)
  message ("unix")
  target_compile_definitions (ssc-test PRIVATE UNIX)
  target_compile_definitions (ssc PRIVATE UNIX)
endif ()

# -g -O0
if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
  message ("debug")
  target_compile_definitions (ssc-test PRIVATE _DEBUG)
  target_compile_definitions (ssc PRIVATE _DEBUG)
  target_compile_options (ssc-test PRIVATE "-g;-O0")
  target_compile_options (ssc PRIVATE "-g;-O0")
else ()
  message ("release")
  target_compile_definitions (ssc-test PRIVATE NDEBUG)
  target_compile_definitions (ssc PRIVATE NDEBUG)
  if (${CMAKE_BUILD_TYPE} MATCHES "MinSizeRel")
    target_compile_options (ssc-test PRIVATE "-Os")
    target_compile_options (ssc PRIVATE "-Os")
  else ()
    target_compile_options (ssc-test PRIVATE "-O3")
    target_compile_options (ssc PRIVATE "-O3")
  endif ()
endif ()

if (${CMAKE_CXX_COMPILER_ID} MATCHES "AppleClang")
  if (${CMAKE_CXX_COMPILER_VERSION} STRLESS "11.0.0")
    message ("elderly")
    target_compile_definitions (ssc-test PRIVATE FUDDYDUDDY)
    target_compile_definitions (ssc PRIVATE FUDDYDUDDY)
  endif ()
endif ()

# target_compile_features (ssc-test PRIVATE cxx_std_17)
# target_compile_features (ssc PRIVATE cxx_std_17)

target_link_libraries (ssc-test PRIVATE Boost::filesystem)
target_link_libraries (ssc-test PRIVATE pthread)

target_link_libraries (ssc PRIVATE Boost::date_time)
target_link_libraries (ssc PRIVATE Boost::filesystem)
target_link_libraries (ssc PRIVATE Boost::program_options)
target_link_libraries (ssc PRIVATE pthread)

install (TARGETS ssc-test DESTINATION ${D})
install (TARGETS ssc DESTINATION ${D})

enable_testing ()

add_test (NAME toasty_toast COMMAND ssc-test -d -i ${TT}/output.txt ${TT}/input.spec)
add_test (NAME toast COMMAND ssc-test -v -f ${TT}/ssc.lst)

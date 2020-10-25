SSCOBJS=attr.o attribute_constructor.o attributes.o avm.o \
css.o css_cache.o \
elem.o parentage.o state.o element.o element_abcd.o element_attributes.o element_classes.o element_efghi.o element_examine.o element_input.o element_jkl.o element_microdata.o \
element_microformats.o element_mno.o element_pqr.o element_s.o element_tuvwxyz.o \
nit.o nitpick.o \
context.o options.o ssc.o standard.o \
microdata_export.o microdata_itemid.o microdata_itemprop.o microdata_itemscope.o microdata_itemtype.o \
family.o field.o microformat_constructor.o microformat_export.o microformats.o property_value.o sibling.o \
html_version.o parse_attribute.o parse_attributes.o parse_bra_ket.o parse_bras_ket.o parse_css.o parse_element.o parse_elements.o parse_ssi.o text.o xhtml_xml.o \
schema_hierarchy.o schema_property.o schema_structure.o schema_type.o schema_version.o \
stats.o stats_impl.o \
symbol.o symbol_table.o \
type.o type_aria.o type_autocomplete.o type_charset.o type_class.o type_colour.o type_core.o type_currency.o type_d.o type_enum.o type_httpequiv.o type_lang.o \
type_media.o type_metaname.o type_mime.o type_paint.o type_reals.o type_rel.o type_sgml.o type_svg_feature.o type_time.o type_transform.o type_url.o type_xmlns.o \
url.o url_parameters.o url_protocol.o url_sanitise.o url_scheme.o \
byteorder.o common.o quote.o \
hook.o irt.o webmention.o webmentions.o \
crosslink.o directory.o external.o fileindex.o headers.o id.o page.o root.o

all: ssc-test ssc test

ssc-test: ssc-test.o
	$(LD) $(LTARGS) ssc-test.o

ssc: $(SSCOBJS)
	$(LD) $(LARGS) $(SSCOBJS)

test: ssc-test ssc
	./ssc-test -d -i tests/ssc-test/output.txt tests/ssc-test/input.spec
	./ssc-test -T -v -f tests/ssc-test/scc.lst

args.h:

attr.h: symbol.h nitpick.h

attribute.h: common.h type.h avm.h parse_attribute.h

attribute_classes.h: attribute.h

attributes.h: attribute.h id.h

avm.h: attr.h type_enum.h elem.h

bigvector.h:

byteorder.h: common.h

common.h: enum.h html_version.h

connection.h: type.h

context.h: css_cache.h hook.h html_version.h irt.h schema_version.h stats.h

crosslink.h: common.h fileindex.h id.h nitpick.h

css.h: common.h nitpick.h

css_cache.h: css.h

directory.h: common.h crosslink.h css_cache.h root.h state.h

elem.h: symbol.h

element.h: attributes.h id.h microdata_itemscope.h microformats_ptr.h microformat_export.h parse_element.h state.h

element_attribute.h: attribute_classes.h tuple.h

element_classes.h: nitpick.h state.h

enum.h: include.h

external.h: context.h

family.h: property.h type.h

fileindex.h:

field.h: property.h type.h

headers.h: context.h

hook.h: url.h

html_version.h: nitpick.h schema_version.h

id.h: common.h enum.h fileindex.h microdata_itemtype.h

include.h: version.h

irt.h: common.h

lexical.h: include.h

microdata_export.h: common.h microdata_itemprop.h

microdata_itemid.h: nitpick.h html_version.h

microdata_itemprop.h: microdata_itemtype.h

microdata_itemscope.h: microdata_export.h

microdata_itemtype.h: nitpick.h html_version.h

microformat.h: elem.h microformat_properties.h type.h

microformat_classes.h: microformat.h

microformat_constructor.h: microformat_classes.h

microformat_export.h: microformat_export_rel.h

microformat_export_rel.h: quote.h

microformat_properties.h: property_classes.h tuple.h

microformats.h: microformat_constructor.h

microformats_ptr.h: microformats.h

nit.h: include.h enum.h

nitnames.h: enum.h

nitpick.h: nit.h lexical.h

options.h: common.h

page.h: byteorder.h css.h element.h fileindex.h id.h microdata_export.h microdata_itemscope.h microformat_export.h parse_elements.h \
        parse_ssi.h schema_version.h stats.h symbol_table.h

parentage.h: html_version.h elem.h

parse_attribute.h: attr.h nitpick.h

parse_attributes.h: elem.h parse_attribute.h

parse_bra_ket.h: enum.h nitpick.h

parse_bras_ket.h: context.h parse_bra_ket.h

parse_css.h: common.h nitpick.h

parse_element.h: elem.h parse_attributes.h

parse_elements.h: parse_element.h parse_bras_ket.h bigvector.h

parse_ssi.h: common.h nitpick.h

prop.h: type.h

property.h: prop.h property_value.h

property_classes.h: property.h

property_value.h: type.h

quote.h: common.h

root.h: nitpick.h

reldef.h:

schema_hierarchy.h: schema_type.h

schema_property.h: schema_type.h microdata_itemtype.h

schema_structure.h: schema_type.h

schema_type.h: nitpick.h schema_version.h symbol.h

schema_version.h:

sibling.h: property.h

standard.h: include.h

state.h: enum.h

stats.h: attr.h elem.h html_version.h

stats_impl.h: stats0.h stats1.h stats2.h html_version.h

stats0.h:

stats1.h: enum.h

stats2.h:

symbol.h: symbol_table.h

symbol_table.h: common.h sz.h

sz.h:

text.h: context.h type.h

tuple.h:

type.h: type_1.h type_2.h type_3.h type_4.h type_aria.h type_autocomplete.h type_base.h type_class.h type_colour.h type_core.h \
        type_currency.h type_enum.h type_enum_vec.h type_httpequiv.h type_lang.h type_master.h type_media.h type_mime.h type_rdf.h \
        type_reals.h type_rel.h type_relational.h type_time.h type_url.h type_van.h type_varied.h type_xmlns.h

type_1.h: type_master.h sz.h

type_2.h: type_master.h sz.h

type_3.h: type_master.h sz.h

type_4.h: type_master.h sz.h

type_aria.h: type_enum.h

type_autocomplete.h: type_enum.h

type_base.h: common.h css.h nitpick.h url.h

type_class.h: type_enum_vec.h

type_colour.h: type_enum.h

type_core.h: type_base.h context.h lexical.h quote.h sz.h

type_currency.h: type_enum.h

type_enum.h: type_master.h

type_enum_vec.h: type_enum.h

type_httpequiv.h: type_enum.h

type_lang.h: type_enum.h

type_master.h: args.h microdata_itemid.h parse_elements.h quote.h symbol.h type_core.h

type_media.h: type_master.h

type_mime.h: type_enum.h

type_rdf.h: type_master.h

type_reals.h: type_master.h

type_rel.h: type_enum_vec.h

type_relational.h: type_rel.h elem.h

type_time.h: type_master.h

type_url.h: microdata_itemtype.h schema_type.h type_master.h

type_van.h: microdata_itemtype.h type_autocomplete.h type_master.h

type_varied.h: type_enum.h elem.h

type_xmlns.h: type_enum.h

url.h: common.h id.h state.h url_protocol.h url_parameters.h

url_parameters.h: common.h

url_protocol.h: symbol.h

url_sanitise.h:

url_scheme.h: url_protocol.h

url_schemes.h: url_scheme.h

version.h:

webmention.h: url.h

webmentions.h: webmention.h

xhtml_xml.h: html_version.h


attr.o: attr.cpp standard.h attr.h context.h quote.h type.h
	$(CPP) $(CCARGS) -c attr.cpp

attribute_constructor.o: attribute_constructor.cpp standard.h attribute.h attribute_classes.h
	$(CPP) $(CCARGS) -c attribute_constructor.cpp

attributes.o: attributes.cpp standard.h attributes.h page.h element_classes.h
	$(CPP) $(CCARGS) -c attributes.cpp

avm.o: avm.cpp standard.h avm.h context.h elem.h type.h
	$(CPP) $(CCARGS) -c avm.cpp

byteorder.o: byteorder.cpp standard.h byteorder.h
	$(CPP) $(CCARGS) -c byteorder.cpp

crosslink.o: crosslink.cpp standard.h context.h crosslink.h quote.h schema_type.h
	$(CPP) $(CCARGS) -c crosslink.cpp

common.o: common.cpp standard.h common.h context.h
	$(CPP) $(CCARGS) -c common.cpp

context.o: context.cpp standard.h context.h hook.h irt.h options.h stats.h
	$(CPP) $(CCARGS) -c context.cpp

css.o: css.cpp standard.h byteorder.h context.h css.h page.h parse_css.h prop.h quote.h type.h url.h
	$(CPP) $(CCARGS) -c css.cpp

css_cache.o: css_cache.cpp standard.h css_cache.h url.h page.h
	$(CPP) $(CCARGS) -c css_cache.cpp

directory.o: directory.cpp standard.h common.h context.h crosslink.h directory.h external.h page.h url.h
	$(CPP) $(CCARGS) -c directory.cpp

elem.o: elem.cpp standard.h elem.h context.h quote.h type.h
	$(CPP) $(CCARGS) -c elem.cpp

element.o: element.cpp standard.h element.h page.h
	$(CPP) $(CCARGS) -c element.cpp

element_abcd.o: element_abcd.cpp standard.h element.h page.h
	$(CPP) $(CCARGS) -c element_abcd.cpp

element_attributes.o: element_attributes.cpp standard.h attribute_classes.h element.h family.h field.h page.h reldef.h sibling.h
	$(CPP) $(CCARGS) -c element_attributes.cpp

element_classes.o: element_classes.cpp standard.h attr.h elem.h element_classes.h
	$(CPP) $(CCARGS) -c element_classes.cpp

element_efghi.o: element_efghi.cpp standard.h attribute_classes.h element.h page.h
	$(CPP) $(CCARGS) -c element_efghi.cpp

element_examine.o: element_examine.cpp standard.h attribute_classes.h element.h page.h parentage.h
	$(CPP) $(CCARGS) -c element_examine.cpp

element_input.o: element_input.cpp standard.h element.h page.h
	$(CPP) $(CCARGS) -c element_input.cpp

element_jkl.o: element_jkl.cpp standard.h element.h page.h
	$(CPP) $(CCARGS) -c element_jkl.cpp

element_microdata.o: element_microdata.cpp standard.h attribute_classes.h element.h page.h
	$(CPP) $(CCARGS) -c element_microdata.cpp

element_microformats.o: element_microformats.cpp standard.h element.h page.h
	$(CPP) $(CCARGS) -c element_microformats.cpp

element_mno.o: element_mno.cpp standard.h attribute_classes.h element.h page.h
	$(CPP) $(CCARGS) -c element_mno.cpp

element_pqr.o: element_pqr.cpp standard.h element.h page.h
	$(CPP) $(CCARGS) -c element_pqr.cpp

element_s.o: element_s.cpp standard.h attribute_classes.h element.h page.h
	$(CPP) $(CCARGS) -c element_s.cpp

element_tuvwxyz.o: element_tuvwxyz.cpp standard.h attribute_classes.h element.h page.h
	$(CPP) $(CCARGS) -c element_tuvwxyz.cpp

external.o: external.cpp standard.h common.h external.h headers.h lexical.h quote.h url.h
	$(CPP) $(CCARGS) -c external.cpp

family.o: family.cpp standard.h family.h
	$(CPP) $(CCARGS) -c family.cpp

field.o: field.cpp standard.h connection.h field.h
	$(CPP) $(CCARGS) -c field.cpp

fileindex.o: fileindex.cpp standard.h fileindex.h directory.h
	$(CPP) $(CCARGS) -c fileindex.cpp

headers.o: headers.cpp standard.h common.h headers.h lexical.h
	$(CPP) $(CCARGS) -c headers.cpp

hook.o: hook.cpp standard.h common.h context.h directory.h element.h external.h hook.h page.h webmentions.h
	$(CPP) $(CCARGS) -c hook.cpp

html_version.o: html_version.cpp standard.h common.h context.h html_version.h type.h
	$(CPP) $(CCARGS) -c html_version.cpp

id.o: id.cpp standard.h element.h id.h
	$(CPP) $(CCARGS) -c id.cpp

irt.o: irt.cpp standard.h context.h common.h directory.h external.h headers.h irt.h page.h
	$(CPP) $(CCARGS) -c irt.cpp

microdata_export.o: microdata_export.cpp standard.h context.h microdata_export.h microdata_itemscope.h
	$(CPP) $(CCARGS) -c microdata_export.cpp

microdata_itemid.o: microdata_itemid.cpp standard.h element.h microdata_itemid.h quote.h
	$(CPP) $(CCARGS) -c microdata_itemid.cpp

microdata_itemprop.o: microdata_itemprop.cpp standard.h microdata_itemprop.h prop.h schema_property.h
	$(CPP) $(CCARGS) -c microdata_itemprop.cpp

microdata_itemscope.o: microdata_itemscope.cpp standard.h context.h microdata_itemtype.h microdata_itemscope.h \
                        page.h prop.h quote.h schema_property.h
	$(CPP) $(CCARGS) -c microdata_itemscope.cpp

microdata_itemtype.o: microdata_itemtype.cpp standard.h microdata_itemtype.h prop.h schema_type.h type_enum_vec.h
	$(CPP) $(CCARGS) -c microdata_itemtype.cpp

microformat_constructor.o: microformat_constructor.cpp standard.h microformat_constructor.h
	$(CPP) $(CCARGS) -c microformat_constructor.cpp

microformat_export.o: microformat_export.cpp standard.h context.h microformat_export.h
	$(CPP) $(CCARGS) -c microformat_export.cpp

microformats.o: microformats.cpp standard.h microformat_constructor.h microformats.h
	$(CPP) $(CCARGS) -c microformats.cpp

nit.o: nit.cpp standard.h context.h nit.h nitnames.h
	$(CPP) $(CCARGS) -c nit.cpp

nitpick.o: nitpick.cpp standard.h context.h nitpick.h
	$(CPP) $(CCARGS) -c nitpick.cpp

options.o: options.cpp standard.h args.h context.h lexical.h options.h type.h
	$(CPP) $(CCARGS) -c options.cpp

page.o: page.cpp standard.h avm.h common.h crosslink.h directory.h element.h page.h text.h type.h url.h url_sanitise.h
	$(CPP) $(CCARGS) -c page.cpp

parentage.o: parentage.cpp standard.h context.h parentage.h
	$(CPP) $(CCARGS) -c parentage.cpp

parse_attribute.o: parse_attribute.cpp standard.h parse_attribute.h quote.h
	$(CPP) $(CCARGS) -c parse_attribute.cpp

parse_attributes.o: parse_attributes.cpp standard.h parse_attributes.h context.h elem.h quote.h type.h
	$(CPP) $(CCARGS) -c parse_attributes.cpp

parse_bra_ket.o: parse_bra_ket.cpp standard.h parse_bra_ket.h common.h elem.h
	$(CPP) $(CCARGS) -c parse_bra_ket.cpp

parse_bras_ket.o: parse_bras_ket.cpp standard.h parse_bras_ket.h text.h xhtml_xml.h
	$(CPP) $(CCARGS) -c parse_bras_ket.cpp

parse_css.o: parse_css.cpp standard.h context.h parse_css.h
	$(CPP) $(CCARGS) -c parse_css.cpp

parse_element.o: parse_element.cpp standard.h context.h parse_element.h quote.h
	$(CPP) $(CCARGS) -c parse_element.cpp

parse_elements.o: parse_elements.cpp standard.h context.h parentage.h parse_elements.h text.h
	$(CPP) $(CCARGS) -c parse_elements.cpp

parse_ssi.o: parse_ssi.cpp standard.h common.h context.h directory.h parse_ssi.h quote.h type.h url.h url_sanitise.h
	$(CPP) $(CCARGS) -c parse_ssi.cpp

property_value.o: property_value.cpp standard.h element.h property_value.h
	$(CPP) $(CCARGS) -c property_value.cpp

quote.o: quote.cpp standard.h quote.h
	$(CPP) $(CCARGS) -c quote.cpp

root.o: root.cpp standard.h common.h fileindex.h root.h quote.h
	$(CPP) $(CCARGS) -c root.cpp

schema_hierarchy.o: schema_hierarchy.cpp standard.h schema_hierarchy.h
	$(CPP) $(CCARGS) -c schema_hierarchy.cpp

schema_property.o: schema_property.cpp standard.h context.h crosslink.h schema_hierarchy.h schema_property.h schema_structure.h schema_type.h type.h
	$(CPP) $(CCARGS) -c schema_property.cpp

schema_structure.o: schema_structure.cpp context.h standard.h schema_structure.h schema_property.h
	$(CPP) $(CCARGS) -c schema_structure.cpp

schema_type.o: schema_type.cpp standard.h context.h schema_type.h quote.h
	$(CPP) $(CCARGS) -c schema_type.cpp

schema_version.o: schema_version.cpp standard.h html_version.h schema_version.h
	$(CPP) $(CCARGS) -c schema_version.cpp

sibling.o: sibling.cpp standard.h connection.h sibling.h
	$(CPP) $(CCARGS) -c sibling.cpp

ssc.o: ssc.cpp standard.h attr.h avm.h context.h css_cache.h directory.h elem.h element_classes.h family.h field.h fileindex.h microdata_itemid.h \
        parentage.h property.h root.h schema_hierarchy.h schema_property.h schema_structure.h sibling.h text.h type.h url.h url_sanitise.h
	$(CPP) $(CCARGS) -c ssc.cpp

ssc-test.o: ssc-test.cpp nitnames.h version.h
	$(CPP) $(CCARGS) -c ssc-test.cpp

standard.o: standard.cpp standard.h
	$(CPP) $(CCARGS) -c standard.cpp

state.o: state.cpp standard.h attr.h elem.h state.h
	$(CPP) $(CCARGS) -c state.cpp

stats.o: stats.cpp standard.h stats.h stats_impl.h
	$(CPP) $(CCARGS) -c stats.cpp

stats_impl.o: stats_impl.cpp standard.h context.h microdata_itemprop.h microdata_itemtype.h nitpick.h stats.h stats_impl.h
	$(CPP) $(CCARGS) -c stats_impl.cpp

symbol.o: symbol.cpp standard.h type.h
	$(CPP) $(CCARGS) -c symbol.cpp

symbol_table.o: symbol_table.cpp standard.h symbol_table.h
	$(CPP) $(CCARGS) -c symbol_table.cpp

text.o: text.cpp standard.h common.h nitpick.h text.h
	$(CPP) $(CCARGS) -c text.cpp

type.o: type.cpp standard.h type.h
	$(CPP) $(CCARGS) -c type.cpp

type_aria.o: type_aria.cpp standard.h type_aria.h
	$(CPP) $(CCARGS) -c type_aria.cpp

type_autocomplete.o: type_autocomplete.cpp standard.h element.h type_autocomplete.h
	$(CPP) $(CCARGS) -c type_autocomplete.cpp

type_charset.o: type_charset.cpp standard.h type_enum.h
	$(CPP) $(CCARGS) -c type_charset.cpp

type_class.o: type_class.cpp standard.h type_class.h
	$(CPP) $(CCARGS) -c type_class.cpp

type_colour.o: type_colour.cpp standard.h type_colour.h
	$(CPP) $(CCARGS) -c type_colour.cpp

type_core.o: type_core.cpp standard.h type_core.h
	$(CPP) $(CCARGS) -c type_core.cpp

type_currency.o: type_currency.cpp standard.h type_currency.h
	$(CPP) $(CCARGS) -c type_currency.cpp

type_d.o: type_d.cpp standard.h type_master.h
	$(CPP) $(CCARGS) -c type_d.cpp

type_enum.o: type_enum.cpp standard.h type.h
	$(CPP) $(CCARGS) -c type_enum.cpp

type_httpequiv.o: type_httpequiv.cpp standard.h type_httpequiv.h
	$(CPP) $(CCARGS) -c type_httpequiv.cpp

type_lang.o: type_lang.cpp standard.h type_lang.h
	$(CPP) $(CCARGS) -c type_lang.cpp

type_media.o: type_media.cpp standard.h type_enum.h type_media.h
	$(CPP) $(CCARGS) -c type_media.cpp

type_metaname.o: type_media.cpp standard.h type_enum_vec.h
	$(CPP) $(CCARGS) -c type_metaname.cpp

type_mime.o: type_mime.cpp standard.h type_mime.h
	$(CPP) $(CCARGS) -c type_mime.cpp

type_paint.o: type_paint.cpp standard.h type.h
	$(CPP) $(CCARGS) -c type_paint.cpp

type_reals.o: type_reals.cpp standard.h type_reals.h
	$(CPP) $(CCARGS) -c type_reals.cpp

type_rel.o: type_rel.cpp standard.h reldef.h type_rel.h
	$(CPP) $(CCARGS) -c type_rel.cpp

type_sgml.o: type_sgml.cpp standard.h context.h type_enum.h
	$(CPP) $(CCARGS) -c type_sgml.cpp

type_svg_feature.o: type_svg_feature.cpp standard.h element.h type_enum.h
	$(CPP) $(CCARGS) -c type_svg_feature.cpp

type_time.o: type_time.cpp standard.h type_time.h
	$(CPP) $(CCARGS) -c type_time.cpp

type_transform.o: type_transform.cpp standard.h type.h
	$(CPP) $(CCARGS) -c type_transform.cpp

type_url.o: type_url.cpp standard.h directory.h type_url.h url.h
	$(CPP) $(CCARGS) -c type_url.cpp

type_xmlns.o: type_xmlns.cpp standard.h type_xmlns.h
	$(CPP) $(CCARGS) -c type_xmlns.cpp

url.o: url.cpp standard.h context.h crosslink.h directory.h quote.h url.h url_protocol.h url_sanitise.h
	$(CPP) $(CCARGS) -c url.cpp

url_parameters.o: url_parameters.cpp standard.h url_parameters.h url_sanitise.h
	$(CPP) $(CCARGS) -c url_parameters.cpp

url_protocol.o: url_protocol.cpp standard.h url_protocol.h url_schemes.h
	$(CPP) $(CCARGS) -c url_protocol.cpp

url_sanitise.o: url_sanitise.cpp standard.h common.h url_sanitise.h
	$(CPP) $(CCARGS) -c url_sanitise.cpp

url_scheme.o: url_scheme.cpp standard.h context.h lexical.h quote.h url_scheme.h url_sanitise.h
	$(CPP) $(CCARGS) -c url_scheme.cpp

webmention.o: webmention.cpp standard.h common.h context.h webmention.h
	$(CPP) $(CCARGS) -c webmention.cpp

webmentions.o: webmentions.cpp standard.h context.h webmentions.h
	$(CPP) $(CCARGS) -c webmentions.cpp

xhtml_xml.o: xhtml_xml.cpp context.h parse_attributes.h quote.h xhtml_xml.h
	$(CPP) $(CCARGS) -c xhtml_xml.cpp


clean:
	rm -rf *.o ssc

install:
	cp ssc /usr/local/bin

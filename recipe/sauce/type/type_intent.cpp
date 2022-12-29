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

struct symbol_entry < html_version, e_conlit > conlit_symbol_table [] =
{   { { HTML_MATH4_22 }, { HTML_UNDEF }, "absolute-complement", icl_absolute_complement },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "absolute-value", icl_absolute_value },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "acceleration", icl_acceleration },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "adjacent", icl_adjacent },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "adjugate", icl_adjugate },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "aligned-equation", icl_aligned_equation },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "and", icl_and },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "angle", icl_angle },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "angle-angle", icl_angle_angle },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "angular-description", icl_angular_description },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "annotation", icl_annotation },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "approaches", icl_approaches },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "approximately", icl_approximately },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "aqueous", icl_aqueous },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "arc", icl_arc },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "area", icl_area },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "array", icl_array },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "average", icl_average },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "base", icl_base },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "binomial-coefficient", icl_binomial_coefficient },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "blank", icl_blank },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "braced-group", icl_braced_group },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "celsius", icl_celsius },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "centimeter", icl_centimeter },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "cents", icl_cents },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "change", icl_change },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "circle", icl_circle },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "common-logarithm", icl_common_logarithm },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "complex-square-root", icl_complex_square_root },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "compound-name", icl_compound_name },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "conditional-probability", icl_conditional_probability },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "congruent", icl_congruent },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "conjugate", icl_conjugate },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "constraint", icl_constraint },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "continued-fraction", icl_continued_fraction },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "day-period", icl_day_period },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "defined-as", icl_defined_as },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "degrees", icl_degrees },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "delimited-subexpression", icl_delimited_subexpression },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "derivative-operator", icl_derivative_operator },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "determinant", icl_determinant },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "diameter", icl_diameter },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "direction-of-approach", icl_direction_of_approach },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "discriminant", icl_discriminant },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "distance", icl_distance },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "divide", icl_divide },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "dollar", icl_dollar },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "element-of", icl_element_of },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "ellipsis", icl_ellipsis },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "empty-set", icl_empty_set },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "equal", icl_equal },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "error-function", icl_error_function },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "euler-number", icl_euler_number },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "evaluate", icl_evaluate },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "evaluates-to", icl_evaluates_to },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "exaannum", icl_exaannum },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "factorial", icl_factorial },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "fenced-group", icl_fenced_group },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "final", icl_final },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "first-derivative", icl_first_derivative },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "focus", icl_focus },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "foot", icl_foot },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "fraction", icl_fraction },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "function-composition", icl_function_composition },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "gas", icl_gas },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "giga-base-pair", icl_giga_base_pair },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "giga-nucleotide", icl_giga_nucleotide },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "gigaannum", icl_gigaannum },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "golden-ratio", icl_golden_ratio },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "gram", icl_gram },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "greater-than", icl_greater_than },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "greater-than-or-equal", icl_greater_than_or_equal },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "greatest-common-divisor", icl_greatest_common_divisor },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "hypotenuse", icl_hypotenuse },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "identically-equal", icl_identically_equal },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "identity-matrix", icl_identity_matrix },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "iff", icl_iff },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "imaginary-part", icl_imaginary_part },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "imaginary-unit", icl_imaginary_unit },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "implies", icl_implies },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "inch", icl_inch },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "indexed-argument", icl_indexed_argument },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "initial", icl_initial },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "integral", icl_integral },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "interchange-rows", icl_interchange_rows },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "interquartile-range", icl_interquartile_range },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "intersection", icl_intersection },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "interval", icl_interval },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "inverse-function", icl_inverse_function },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "inverse-matrix", icl_inverse_matrix },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "kilo-nucleotide", icl_kilo_nucleotide },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "kiloannum", icl_kiloannum },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "kilogram", icl_kilogram },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "kilometer", icl_kilometer },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "kilonewton", icl_kilonewton },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "least-common-denominator", icl_least_common_denominator },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "least-common-multiple", icl_least_common_multiple },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "length-of-segment", icl_length_of_segment },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "less-than", icl_less_than },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "less-than-or-equal", icl_less_than_or_equal },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "limit", icl_limit },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "line", icl_line },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "line-segment", icl_line_segment },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "liquid", icl_liquid },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "list-separator", icl_list_separator },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "liter", icl_liter },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "magnitude", icl_magnitude },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "matrix", icl_matrix },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "matrix-by", icl_matrix_by },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "matrix-order", icl_matrix_order },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "mean-absolute-deviation", icl_mean_absolute_deviation },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "measure", icl_measure },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "measure-of-angle", icl_measure_of_angle },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "mega-nucleotide", icl_mega_nucleotide },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "megaannum", icl_megaannum },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "meter", icl_meter },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "miles-per-hour", icl_miles_per_hour },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "milliliter", icl_milliliter },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "minus", icl_minus },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "more-than", icl_more_than },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "natural-logarithm", icl_natural_logarithm },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "negated-operator", icl_negated_operator },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "negative", icl_negative },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "negative-ion", icl_negative_ion },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "neutral", icl_neutral },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "not-element-of", icl_not_element_of },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "not-equal", icl_not_equal },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "nth-derivative", icl_nth_derivative },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "nucleotide", icl_nucleotide },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "number", icl_number },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "number-of", icl_number_of },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "number-set", icl_number_set },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "operator-range", icl_operator_range },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "opposite", icl_opposite },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "or", icl_or },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "ordered-pair", icl_ordered_pair },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "ordinal-mark", icl_ordinal_mark },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "ounce", icl_ounce },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "outcome", icl_outcome },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "parallel", icl_parallel },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "parenthetical", icl_parenthetical },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "particular-value-of", icl_particular_value_of },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "percent", icl_percent },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "permutation-symbol", icl_permutation_symbol },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "perpendicular", icl_perpendicular },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "petaannum", icl_petaannum },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "ph", icl_ph },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "pi", icl_pi },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "piecewise", icl_piecewise },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "plus", icl_plus },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "plus-or-minus", icl_plus_or_minus },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "point", icl_point },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "point-at", icl_point_at },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "polynomial-arguments-degree-center", icl_polynomial_arguments_degree_center },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "position", icl_position },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "positive", icl_positive },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "positive-ion", icl_positive_ion },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "pound", icl_pound },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "power", icl_power },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "probability", icl_probability },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "progression", icl_progression },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "proper-subset-of", icl_proper_subset_of },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "proper-superset-of", icl_proper_superset_of },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "qualified-operator", icl_qualified_operator },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "radian", icl_radian },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "radius", icl_radius },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "range-separator", icl_range_separator },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "rate", icl_rate },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "ratio", icl_ratio },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "ray", icl_ray },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "real-numbers", icl_real_numbers },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "real-part", icl_real_part },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "rectangle", icl_rectangle },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "remainder", icl_remainder },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "remainder-function", icl_remainder_function },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "repeating-digits", icl_repeating_digits },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "root", icl_root },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "second-derivative", icl_second_derivative },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "sequence-range", icl_sequence_range },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "set", icl_set },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "set-difference", icl_set_difference },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "shape", icl_shape },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "side-angle-side", icl_side_angle_side },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "side-side-side", icl_side_side_side },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "solid", icl_solid },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "square", icl_square },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "square-root", icl_square_root },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "subset-of-or-equal", icl_subset_of_or_equal },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "such-that", icl_such_that },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "sum", icl_sum },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "system-of-equations", icl_system_of_equations },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "teraannum", icl_teraannum },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "time-separator", icl_time_separator },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "times", icl_times },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "ton", icl_ton },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "transform", icl_transform },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "translates-to", icl_translates_to },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "translation", icl_translation },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "transpose", icl_transpose },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "triangle", icl_triangle },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "triangle-similarity", icl_triangle_similarity },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "trigonometric-function", icl_trigonometric_function },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "union", icl_union },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "unit", icl_unit },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "unit-vector", icl_unit_vector },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "variable", icl_variable },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "vector", icl_vector },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "velocity", icl_velocity },
    { { HTML_MATH4_22 }, { HTML_UNDEF }, "volume", icl_volume } };

void conlit_init (nitpick& nits)
{   type_master < t_conlit > :: init (nits, conlit_symbol_table, sizeof (conlit_symbol_table) / sizeof (symbol_entry < html_version, e_conlit >)); }
   
parser grammar RecetasParser;
options { tokenVocab=RecetasLexer; }
/*
 * Parser rules
 */
prog            : section* EOF; 

section         : section_header section_body?;
section_header  : SECTION_BEGIN name_=TEXT;
section_body    : ((expression | time_section)? NEWLINE+)+;

time_section    : delta_=ammount TIME_SEC_END;
expression      : assignment_=assignment rhs_=rhs;
/* rhs             : id_=id details_=details?; */

rhs             : id_=id details_=details #rhs_expression
                | details_=details #rhs_assign
                | details_=id #rhs_assign;

details         : item (SEP item)* utensil_=utensil? temp_=temperature?;
utensil         : USAGE_SPEC TEXT;

assignment      : asignee_=id ASSIGN;

/* item            : (ammount_=ammount SPECIFIER?)? (text | id); */
item            : ammount_=ammount SPECIFIER? name_=text #item_Raw
                | ammount_=ammount SPECIFIER? name_=id #item_AmmountVariable
                | name_=text #item_UnitRaw
                | name_=id #item_UnitVariable;

text            : TEXT;
id              : ID;
ammount         : quantity_=NUMBER unit_=ID?;

temperature     : TEMP_SPEC NUMBER ID# temperature_numeric
                | TEMP_SPEC ID # temperature_id;

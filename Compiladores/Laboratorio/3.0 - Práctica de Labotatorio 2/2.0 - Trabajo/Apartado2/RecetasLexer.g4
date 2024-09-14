lexer grammar RecetasLexer;

/*
 * Lexer rules
 */
// High level rules
ING_SART        : '"' -> pushMode(TXT_BLOCK), skip;
SECTION_BEGIN   : '>>' ' '? -> pushMode(TXT_BLOCK);
TIME_SEC_END    : ':';
ASSIGN          : '<-';
COMMENT_START   : '//' -> skip, pushMode(COMMENT_MODE);

// Specificators
TEMP_SPEC       : 'a';
SPECIFIER       : 'de';
USAGE_SPEC      : 'con';
SEP             : ',';

// Types
    // Numbers are by default float
/* NUMBER          : DIGIT+ ('.' DIGIT+)? -> pushMode(UNIT_MODE); */
NUMBER          : DIGIT+ ('.' DIGIT+)?;

// General identifiers
ID              : LETTER (LETTER | DIGIT | '_')*;
// Low level rules
fragment LETTER : [a-zA-Z];
fragment DIGIT  : [0-9];

// Ignores
WHITESPACE      : ' ' -> skip;
NEWLINE         : [\r\n];

// Text block mode
mode TXT_BLOCK;

TEXT            : (WORD | WHITESPACE)+;
WORD            : LETTER+;
SECTION_END     : [\n\r] -> popMode, skip;
INGREDIENT_END  : '"' -> popMode, skip;

/*mode UNIT_MODE;

UNIT            : [a-zA-Z]+;
UNIT_NL         : [\n\r] -> popMode, skip;
UNIT_STOP       : . -> popMode;*/

mode COMMENT_MODE;
COMMENT_STOP    : '.' -> popMode, skip;
COMMENT         : ~[\n\r] -> skip;

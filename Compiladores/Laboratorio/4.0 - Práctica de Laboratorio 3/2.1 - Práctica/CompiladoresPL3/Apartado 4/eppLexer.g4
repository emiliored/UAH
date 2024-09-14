lexer grammar eppLexer;


// Fragments
ASSIGN                      : 'asignar';

// Control structures
IF                          : 'si';
WHILE                       : 'mientras';
FOR                         : 'durante';

FOR_INIT_SEP                : ',';

// Language
ENDL                        : ';P';

COND_END                    : '???';
BLOCK_END                   : 'terminar';
BLOCK_START                 : '->';

TIMES                       : '*';
PLUS                        : '+';
MINUS                       : '-';
DIVIDED                     : '/';
LESS_THAN                   : '<';
MORE_THAN                   : '>';
LESS_EQUALS                 : '<=';
MORE_EQUALS                 : '>=';
SET                         : '=';

OPEN_EXPR_BLOCK             : '(';
CLOSE_EXPR_BLOCK            : ')';

fragment INT                : DIGIT+;
fragment DIGIT              : [0-9];
fragment LETTER             : [a-zA-Z];
fragment STRING_DELIMITER   : '"';

NUMBER                      : INT;
DECIMAL_SEP                 : '.';

BOOL_CONST                  : 'true'
                            | 'false';

STRING_START                : STRING_DELIMITER -> skip, pushMode(STRING_MODE);

WS                          : ' '+ -> skip;
NEWLINE                     : [\n\r]+ -> skip;
COMMENT_START               : '#' -> pushMode(COMMENT_MODE);

ID                          : ('_' | LETTER) (LETTER | DIGIT)*;

mode COMMENT_MODE;
COMMENT                     : (~[\n\r]*)[\n\r] -> skip, popMode;

mode STRING_MODE;
STRING                      : ~["]*;
STRING_END                  : '"' -> skip, popMode;

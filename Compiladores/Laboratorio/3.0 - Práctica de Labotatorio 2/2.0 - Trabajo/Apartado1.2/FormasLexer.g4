lexer grammar FormasLexer;

// Header
IMGDIMSPEC          : 'imgdim:';
SHPDIMSPEC          : 'shpdim:';

INT                 : DIGIT+;

fragment DIGIT      : [0-9];

// Shapes
SEP                 : ',';
ROWSEP              : '|';

SHAPES_START        : '>>>';
SHAPES_END          : '<<<';

SHAPE               : [a-z]+;

NEWLINE             : [\n\r] -> skip;
WS                  : ' ' -> skip;

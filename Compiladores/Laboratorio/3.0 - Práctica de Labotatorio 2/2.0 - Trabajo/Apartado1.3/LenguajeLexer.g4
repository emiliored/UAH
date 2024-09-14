lexer grammar LenguajeLexer;

// Separadores:
SEP :   ';P';
IG  :   '=';
OPL : [><];
OP  : [+-];

// Ignores
WH      : ' ' -> skip;
NEWLINE         : [\r\n]+;

COMENTARIOENTRAR    :   '#' -> skip, pushMode(COMENTARIO_MODE);
ASIGNAR :   'asignar' -> pushMode(ASIGNAR_MODE);
IF_SEP  :   '???' -> pushMode(IF_MODE);
MOSTRAR  :   'mostrar' -> pushMode(MOSTRAR_MODE);

mode COMENTARIO_MODE;
COMMENT_STOP    : [\n\r] -> popMode, skip;
COMMENT         : ~[\n\r] -> skip;

mode ASIGNAR_MODE;
SEP_ASIGNAR :   ';P' -> popMode;
VARIABLE_ASIGNAR    :   ID;

mode IF_MODE;
IF_SALIR    :   'terminar' -> popMode, skip;
SI_MODE     :   'si ->';
NO_MODE     :   'no ->';

mode MOSTRAR_MODE;
SEP_MOSTRAR :   ';P' -> popMode;
VARIABLE_MOSTRAR    :   ID;

// General identifiers
NUMERO  :   DIGITO+ (. DIGITO+)?;
ID              : (LETRA | DIGITO)+;
// Low level rules
fragment LETRA : [a-zA-Z];
fragment DIGITO  : [0-9];
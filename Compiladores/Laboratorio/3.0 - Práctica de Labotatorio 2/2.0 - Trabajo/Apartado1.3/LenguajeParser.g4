parser grammar LenguajeParser;

options{
    tokenVocab=LenguajeLexer;
}
/*
 * Parser rules
 */
// prog          : linea* EOF;
prog          : asignacion EOF;

linea         : asignacion
              | COMENTARIOENTRAR COMMENT
              | comprobacion
              | MOSTRAR ID SEP
              ;

asignacion    : ASIGNAR VARIABLE_ASIGNAR IG expresion SEP_ASIGNAR;
comprobacion  : ID OPL expresion IF_SEP;
expresion     : ID (OP ID)*;
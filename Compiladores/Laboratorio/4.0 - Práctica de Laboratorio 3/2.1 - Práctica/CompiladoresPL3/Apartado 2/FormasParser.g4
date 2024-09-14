parser grammar FormasParser;

options{
    tokenVocab=FormasLexer;
}

geom                : dimensions shapes EOF;
dimensions          : imgdim SEP shpdim;

imgdim              : IMGDIMSPEC size_=INT;
shpdim              : SHPDIMSPEC size_=INT;

shapes              : SHAPES_START row (ROWSEP row)* SHAPES_END;

row                 : SHAPE (SEP SHAPE)*;

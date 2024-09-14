parser grammar CSVParser;

options{
    tokenVocab=CSVLexer;
}

file    : (header)? (line)* EOF;

header  : cell* NEWLINE;

line    : cell* NEWLINE;
cell    : (TEXT_BLOCK | CONTENT);

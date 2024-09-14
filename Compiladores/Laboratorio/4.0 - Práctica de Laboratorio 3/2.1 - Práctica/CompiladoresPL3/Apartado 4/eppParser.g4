parser grammar eppParser;
options { tokenVocab=eppLexer; }

prog                        : (instruction ENDL | comment | control)* EOF;

instruction                 : assignation
                            | procedure;

assignation                 : ASSIGN symbol=ID SET expr_start            #assign_initializing
                            | symbol=ID SET expr_start                   #assign
                            ;

procedure                   : method=ID (args=ID)*;

// Control structures
control                     : if                                   #control_if
                            | while                                #control_while
                            | for                                  #control_for
                            ;

if                          : condition IF block;
while                       : condition WHILE block;
for                         : for_cond FOR block;

for_cond                    : assignation FOR_INIT_SEP expr_start FOR_INIT_SEP assignation COND_END;

// Building blocks
condition                   : expr COND_END;

expr_start                  : expr;
expr                        : OPEN_EXPR_BLOCK expr CLOSE_EXPR_BLOCK     #expr_parenthesis
                            | lhs=expr LESS_THAN    rhs=expr               #expr_less_than
                            | lhs=expr MORE_THAN    rhs=expr               #expr_more_than
                            | lhs=expr MORE_EQUALS  rhs=expr               #expr_more_equals
                            | lhs=expr LESS_EQUALS  rhs=expr               #expr_less_equals
                            | lhs=expr DIVIDED      rhs=expr               #expr_division
                            | lhs=expr TIMES        rhs=expr               #expr_multiplication
                            | lhs=expr PLUS         rhs=expr               #expr_addition
                            | lhs=expr MINUS        rhs=expr               #expr_substraction
                            | lhs=expr ID           rhs=expr               #expr_variable
                            | ID                                           #expr_variable
                            | NUMBER                                       #expr_integer
                            | NUMBER (DECIMAL_SEP NUMBER)                  #expr_float
                            | BOOL_CONST                                   #expr_bool
                            | STRING                                       #expr_string
                            ;

block                       : BLOCK_START (instruction ENDL | comment | control)* BLOCK_END;

// Comments
comment                     : COMMENT_START;

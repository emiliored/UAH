#!/bin/python3
from typing import Dict
from antlr4.RuleContext import ParseTreeVisitor, Trees
from bin.RecetasLexer import CommonTokenStream, FileStream, ParseTreeWalker, RecetasLexer
from bin.RecetasParser import RecetasParser
from sys import argv

from error import RecipesErrorManager

from visitor import RecipeVisitor, UnitTypes

from lang.keywords import Symbol as SymbolType

import interpreter.reader as reader
from semantic_checker import check

from lang.units import Unit

if __name__ == "__main__":
    file_stream = FileStream(argv[1])
    lexer = RecetasLexer(file_stream)
    stream = CommonTokenStream(lexer)
    parser = RecetasParser(stream)
    tree = parser.prog()

    # Temporal error manager
    error_manager = RecipesErrorManager()
    parser.addErrorListener(error_manager)

    visitor = RecipeVisitor()
    variables, AST = visitor.run(tree)
    # Check AST
    check(AST)

    ingredientes: Dict[str, Unit] = reader.get_stats(AST)

    print('Lista de ingredientes: ')
    for name, ammount in ingredientes.items():
        print(f'{name}:\t\t {ammount}')

    print('\nLista de utensilios: ')
    utensil_list = set() 
    for var, type in variables.items():
        if type == SymbolType.UTENSIL:
            utensil_list.add(var)

    utensil_list = utensil_list.union(reader.get_implicit_utensils(AST))
    for utensil in utensil_list:
        print(utensil)

    print(f'\nTiempo total: {reader.get_total_time(AST)}s')
    pass

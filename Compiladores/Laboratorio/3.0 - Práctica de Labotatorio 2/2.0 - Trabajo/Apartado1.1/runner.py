import sys
from antlr4 import *
from antlr4.tree.Trees import Trees
from bin.CSVLexer import CSVLexer as Lexer
from bin.CSVParser import CSVParser as Parser
 
def main(argv):
    # Inicializamos la entrada de datos
    input_stream = FileStream(argv[1])
    # Conectamos con el lexer
    lexer = Lexer(input_stream)
    # Inicializamos el canal de tokens
    tokens = CommonTokenStream(lexer)
    # Preparamos el parser
    parser = Parser(tokens)
    # Generamos el arbol a partir del axioma de la gramática
    tree = parser.file_()
    # Mostrar el arbol por consola
    print(Trees.toStringTree(tree, None, parser))
    
 
if __name__ == '__main__':
    main(sys.argv)

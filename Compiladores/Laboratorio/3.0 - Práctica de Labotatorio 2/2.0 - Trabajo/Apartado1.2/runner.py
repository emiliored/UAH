import sys
from antlr4 import *
from bin.FormasLexer import FormasLexer as Lexer
from bin.FormasParser import FormasParser as Parser
from antlr4.tree.Trees import Trees
 
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
    tree = parser.geom()
    # Mostrar el arbol por consola
    print(Trees.toStringTree(tree, None, parser))
    
 
if __name__ == '__main__':
    main(sys.argv)

import sys
from antlr4 import *
from antlr4.tree.Trees import Trees
from bin.CSVLexer import CSVLexer as Lexer
from bin.CSVParser import CSVParser as Parser
from bin.CSVParserVisitor import CSVParserVisitor

class Visitor(CSVParserVisitor):
    tabla_simbolos:list = []
    
    def visitFile(self, ctx: Parser.FileContext):
        self.tabla_simbolos = self.visit(ctx.header())
        ret:str = ''
        for i, line in enumerate(ctx.line()):
            ret += self.visit(line)
            if not (i == len(ctx.line())-1):
                ret += ','
        return '[ ' + ret +' ]'

    def visitHeader(self, ctx: Parser.HeaderContext):
        return [self.visit(cell) for cell in ctx.cell()]

    def visitLine(self, ctx: Parser.LineContext):
        ret:str = ''
        for i, cell in enumerate(ctx.cell()):
            ret += ' ' + self.tabla_simbolos[i]+': '
            ret += '\'' + self.visit(cell) + '\''
            if not (i == len(ctx.cell())-1):
                ret += ','
        return '{' + ret + ' }'

    def visitContent(self, ctx: Parser.ContentContext):
        return str(ctx.CONTENT())

    def visitText_block(self, ctx: Parser.Text_blockContext):
        return str(ctx.TEXT_BLOCK())
    
 
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
    print(Trees.toStringTree(tree, None, parser),"\n")
    # Visitor
    v:Visitor = Visitor()
    resultado:str = v.visit(tree)
    print(resultado)
    
 
if __name__ == '__main__':
    main(sys.argv)

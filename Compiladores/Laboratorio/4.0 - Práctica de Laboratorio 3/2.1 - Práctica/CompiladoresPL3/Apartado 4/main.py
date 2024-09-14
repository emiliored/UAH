from antlr4 import CommonTokenStream, FileStream
from bin.eppLexer import eppLexer
from bin.eppParser import eppParser
from sys import argv
from visitor import EPPVisitor

if __name__ == "__main__":
    file_stream = FileStream(argv[1])
    lexer = eppLexer(file_stream)
    stream = CommonTokenStream(lexer)
    parser = eppParser(stream)
    tree = parser.prog()

    visitor = EPPVisitor()
    AST = visitor.visit(tree)
    print(AST)


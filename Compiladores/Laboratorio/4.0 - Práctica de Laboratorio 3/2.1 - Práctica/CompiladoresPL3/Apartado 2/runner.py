from enum import Enum, EnumMeta
import sys
from antlr4 import *
from tkinter import *
from bin.FormasLexer import FormasLexer as Lexer
from bin.FormasParser import FormasParser as Parser
from antlr4.tree.Trees import Trees
from bin.FormasParserVisitor import FormasParserVisitor
 
class Visitor(FormasParserVisitor):
    class FigurasMeta(EnumMeta):
        def __contains__(self, obj: str) -> bool:
            return str(obj) in [str(v.value) for v in self.__members__.values()] 

    class Figuras(Enum, metaclass = FigurasMeta):
        CIRCULO     = "circulo"
        CUADRADO    = "cuadrado"
        TRIANGULO   = "triangulo"

        def __eq__(self, __o: object) -> bool:
            return True if (str(self.value) == str(__o)) else False

    # Atributos elementos Parser
    imgdim:int      = -1
    shpdim:int      = -1
    filas:list      = []
    # Atributos para la GUI
    window:Tk       = None
    canvas:Canvas   = None

    def __init__(self, tree:Parser.GeomContext) -> None:
        self.visit(tree=tree)
    
    def visitGeom(self, ctx: Parser.GeomContext):
        self.visit(ctx.dimensions())
        self.visit(ctx.shapes())
        return

    def visitShapes(self, ctx: Parser.ShapesContext):
        for row in ctx.row():
            self.filas.append(self.visit(row))
        return 

    def visitRow(self, ctx: Parser.RowContext):
        ret:list = []
        for index_shape in range(len(ctx.SHAPE())):
            shape:str = str(ctx.SHAPE(index_shape))
            if shape in Visitor.Figuras:
                ret.append(shape)
        return ret

    def visitDimensions(self, ctx: Parser.DimensionsContext):
        self.imgdim = self.visit(ctx.imgdim())
        self.shpdim = self.visit(ctx.shpdim())
        return

    def visitImgdim(self, ctx: Parser.ImgdimContext):
        return int(ctx.INT().__str__())

    def visitShpdim(self, ctx: Parser.ShpdimContext):
        return int(ctx.INT().__str__())

    def __str__(self) -> str:
        return "imgdim: " + str(self.imgdim) + " - shpdim: " + str(self.shpdim) + " - filas: " + str(self.filas)

    def dibujar(self):
        # Dibujar ventana
        self.window = Tk()
        self.window.configure(background = "white")
        self.window.title("Formas")
        # Dibujar canvas
        self.canvas = Canvas(self.window, width=self.imgdim, height = self.imgdim, bg="gray")
        self.canvas.pack()
        # Dibujar elementos
        color:str = "pink"
        for index_fila, fila in enumerate(self.filas):
            for index_elemento, elemento in enumerate(fila):
                if (elemento == Visitor.Figuras.CIRCULO):
                    self.canvas.create_oval((index_elemento*self.shpdim), (index_fila*self.shpdim),\
                        ((index_elemento+1)*self.shpdim), ((index_fila+1)*self.shpdim), fill = color)
                    next
                if (elemento == Visitor.Figuras.CUADRADO):
                    self.canvas.create_rectangle((index_elemento*self.shpdim), (index_fila*self.shpdim),\
                        ((index_elemento+1)*self.shpdim), ((index_fila+1)*self.shpdim), fill =color)
                    next
                if (elemento == Visitor.Figuras.TRIANGULO):
                    self.canvas.create_polygon((index_elemento*self.shpdim), (index_fila*self.shpdim),\
                        ((index_elemento+1)*self.shpdim), (index_fila*self.shpdim),\
                        int(((index_elemento*self.shpdim)+((index_elemento+1)*self.shpdim))/2), ((index_fila+1)*self.shpdim), fill = color)
                    next

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
    # Visitor
    v:Visitor = Visitor(tree=tree)
    print(v)
    v.dibujar()
    input("Enter para salir")
 
if __name__ == '__main__':
    main(sys.argv)


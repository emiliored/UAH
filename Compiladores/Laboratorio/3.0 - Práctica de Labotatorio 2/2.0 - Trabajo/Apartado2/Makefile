all: RecetasParser.g4 RecetasLexer.g4
	antlr4 $? -Dlanguage=Python3 -visitor -o bin 

clean: 
	rm -rvf bin 

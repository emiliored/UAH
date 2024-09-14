all: eppLexer.g4 eppParser.g4
	antlr4 $? -Dlanguage=Python3 -visitor -o bin 

clean: 
	rm -rvf bin 

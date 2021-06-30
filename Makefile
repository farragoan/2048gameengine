default:
	clear
	bison -d parser.y -o parser.tab.cc
	flex -o parser.yy.cc lexer.l
	g++ -w -o out -g parser.tab.cc parser.yy.cc game.cpp

clean:
	rm -f lex.yy.c parser.tab.* *.out parser.output out *.yy.cc
CC = gcc
CFLAGS = -g -Wall
SRC = src
REQ = $(SRC)/lexer.l $(SRC)/parser.y $(SRC)/calculator.c $(SRC)/colour.c
calculator : $(REQ)
	bison -d $(SRC)/parser.y
	flex -o calculator.lex.c $(SRC)/lexer.l
	$(CC) $(CFLAGS) parser.tab.c calculator.lex.c $(SRC)/calculator.c $(SRC)/colour.c -o $@

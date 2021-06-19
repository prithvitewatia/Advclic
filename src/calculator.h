#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
// Declarations for calculator

// Interface to the lexer
extern int yylineno;
extern int yyparse();
void yyerror(char *s,...);

// Nodes in the abstract syntax tree
struct AST{
    int nodetype;
    struct AST *l;
    struct AST *r;
};

typedef struct AST ast;

typedef struct NUMVAL{
    int nodetype;   //Type K for constant
    double number;
}numval;

// Build an ast
ast* newast(int nodetype,ast* l,ast* r);
ast* newnum(double d);

// eval an ast
double eval(ast* );

// delete and free the ast
void treefree(ast* );

// Utility function help
void help();
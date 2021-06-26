#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<math.h>
// Declarations for calculator

// Interface to the lexer
extern int yylineno;
extern int yyparse();
void yyerror(char *s,...);

// An enum for built-in functions
enum builtin_fn{
    // Exponential and logarithmic
    B_exp=1,
    B_exp2,
    B_log2,
    B_log10,
    B_log,
    // Trignometric
    B_cos,
    B_sin,
    B_tan,
    B_asin,
    B_acos,
    B_atan,
    B_sinh,
    B_cosh,
    B_tanh,
    B_asinh,
    B_acosh,
    B_atanh,
    // Algebric 
    B_sqrt,
    B_cbrt,
    B_abs,
    B_ceil,
    B_floor,
    // Error and gamma functions
    B_erf,
    B_tgamma
};

typedef struct AST ast;

// Nodes in the abstract syntax tree
struct AST{
    int nodetype;
    struct AST *l;
    struct AST *r;
};

typedef struct NUMVAL{
    int nodetype;   //Type K for constant
    double number;
}numval;

// Build an ast
ast* newast(int nodetype,ast* l,ast* r);
ast* newcmp(int cmptype,ast* l,ast* r);
ast* newnum(double d);
ast* newcall(int functype,ast* explist);

// eval an ast
double eval(ast* );

// delete and free the ast
void treefree(ast* );

// Utility function help
void help();
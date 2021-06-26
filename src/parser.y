%{
    #include "src/calculator.h"
    #include "src/colour.h"

    int yylex();
%}

%union {
    ast* a;
    double d;
    int fn;
}

// Declare tokens
%token <d> NUMBER
%token <fn> FUNCTION
%token NOT BITAND BITOR BITNOT AND OR XOR
%token ECMP GLCMP               // Equality comparison and greater and less than comparison
%token EOL

//
%type <a> exp
%type <fn> ECMP GLCMP
// Writing operator Precedence
%nonassoc FUNCTION
%left OR
%left AND
%left BITOR
%left XOR
%left BITAND
%left ECMP
%left GLCMP
%left '+' '-'
%left '*' '/' '%'
%nonassoc NOT BITNOT UMINUS

%%
calclist: /*nothing*/
    | calclist exp EOL              {   double res = eval($2);      // evaluate the ast
                                        printf("\033[1;32m%lf\n\033[0m",res);   //Print the result
                                        treefree($2);    // Free the memory
                                        printCOLOUR("blue","[Expr]");
                                    }
    | calclist EOL                  {
                                        printCOLOUR("blue","[Expr]");
                                    }
    | calclist 'h' EOL              {
                                        help();
                                    }
    | calclist 'q' EOL              {
                                        exit(EXIT_SUCCESS);
                                    }
    | error EOL                     {
                                        yyerrok;
                                        printCOLOUR("blue","[Expr]");
                                    }
    ;
exp:  NOT exp                       { $$ = newast('n',$2,NULL);}
    | BITNOT exp                    { $$ = newast('~',$2,NULL);}
    | exp BITAND exp                { $$ = newast('&',$1,$3);}
    | exp BITOR exp                 { $$ = newast('|',$1,$3);}
    | exp XOR exp                   { $$ = newast('x',$1,$3);}
    | exp OR exp                    { $$ = newast('o',$1,$3);}
    | exp AND exp                   { $$ = newast('a',$1,$3);}
    | exp ECMP exp                  { $$ = newcmp($2,$1,$3);}
    | exp GLCMP exp                 { $$ = newcmp($2,$1,$3);}
    | exp '+' exp                   { $$ = newast('+',$1,$3);}
    | exp '-' exp                   { $$ = newast('-',$1,$3);}
    | exp '*' exp                   { $$ = newast('*',$1,$3);}
    | exp '/' exp                   { $$ = newast('/',$1,$3);}
    | exp '%' exp                   { $$ = newast('%',$1,$3);}
    | '(' exp ')'                   { $$ = $2;}
    | '-' exp %prec UMINUS          { $$ = newast('M',$2,NULL);}
    | NUMBER                        { $$ = newnum($1);}
    | FUNCTION '(' exp ')'          { $$ = newcall($1,$3);}
    ;
%%

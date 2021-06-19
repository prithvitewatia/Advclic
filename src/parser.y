%{
    #include "src/calculator.h"
    #include "src/colour.h"

    int yylex();
%}

%union {
    ast* a;
    double d;
}

// Declare tokens
%token <d> NUMBER;
%token EOL

// Assigns a value <a> to exp, factor and term
%type <a> exp factor term util
%%
calclist: /* nothing */
        | calclist exp EOL          {   double result=eval($2); // Evaluate the ast
                                        printf("\033[0;32m%lf\n\033[0m",result);    //Print the result
                                        treefree($2);   //Free the memory
                                        printCOLOUR("\033[0;34m","[Expr]");
                                    }
        | calclist EOL              {
                                        printCOLOUR("\033[0;34m","[Expr]");
                                    }
        | calclist util EOL
        ;
exp: factor
    | exp '+' factor                {
                                        $$ = newast('+',$1,$3);
                                    }
    | exp '-' factor                {
                                        $$ = newast('-',$1,$3);
                                    }
    ;
factor: term
    |   factor '*' term             {
                                        $$ = newast('*',$1,$3);
                                    }
    |   factor '/' term             {
                                        $$ = newast('/',$1,$3);
                                    }
    |   factor '%' term             {
                                        $$ = newast('%',$1,$3);
                                    }
    ;
term: NUMBER                        {
                                        $$ = newnum($1);
                                    }
    | '(' exp ')'                   {
                                        $$ = $2;
                                    }
    | '-' term                      {
                                        $$ = newast('M',$2,NULL);
                                    }
    ;
util:   'h'                           {
                                        help();
                                    }
    |   'q'                         {
                                        exit(0);
                                    }

%%

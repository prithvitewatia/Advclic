/* recognize tokens for the calculator */
%option noyywrap nodefault yylineno
%{
    #include "src/calculator.h"
    #include "parser.tab.h"
%}

/*float exponent*/
EXP         ([Ee][-+]?[0-9]+)

%%
"h"                                 {   return yytext[0]; }
"q"                                 {   return yytext[0]; }
"+"|"-"|"*"|"/"|"|"|"("|")"         {   return yytext[0]; }
[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}?    {   yylval.d = atof(yytext);
                        return NUMBER;
                    }
\n                  {
                        return EOL;
                    }
"//".*
[ \t]               {
                        /* ignore whitespace */
                    }
.                   {
                        yyerror("Invalid character in expression %c\n",*yytext);
                    }

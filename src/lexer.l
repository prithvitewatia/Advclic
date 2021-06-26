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
"+"|"-"|"*"|"/"|"%"|"("|")"|","     {   return yytext[0]; }
">"                  {yylval.fn = 1; return GLCMP;}
"<"                  {yylval.fn = 2; return GLCMP;}
"!="                 {yylval.fn = 3; return ECMP;}
"=="                 {yylval.fn = 4; return ECMP;}
">="                 {yylval.fn = 5; return GLCMP;}
"<="                 {yylval.fn = 6; return GLCMP;}
"and"                {yylval.fn = 263; return AND;}
"or"                 {yylval.fn = 264; return OR;}
"xor"                {yylval.fn = 265; return XOR;}
"not"                {yylval.fn = 266; return NOT;}
"~"                  {yylval.fn = 267; return BITNOT;}
"&"                  {yylval.fn = 268; return BITAND;}
"|"                  {yylval.fn = 269; return BITOR;}
"exp"                {yylval.fn = B_exp;return FUNCTION;}
"exp2"               {yylval.fn = B_exp2;return FUNCTION;}
"log2"               {yylval.fn = B_log2;return FUNCTION;}
"log10"              {yylval.fn = B_log10;return FUNCTION;}
"log"                {yylval.fn = B_log;return FUNCTION;}
"cos"                {yylval.fn = B_cos;return FUNCTION;}
"sin"                {yylval.fn = B_sin;return FUNCTION;}
"tan"                {yylval.fn = B_tan;return FUNCTION;}
"asin"               {yylval.fn = B_asin; return FUNCTION;}
"acos"               {yylval.fn = B_acos; return FUNCTION;}
"atan"               {yylval.fn = B_atan; return FUNCTION;}
"sinh"               {yylval.fn = B_sinh; return FUNCTION;}
"cosh"               {yylval.fn = B_cosh; return FUNCTION;}
"tanh"               {yylval.fn = B_tanh; return FUNCTION;}
"asinh"              {yylval.fn = B_asinh; return FUNCTION;}
"acosh"              {yylval.fn = B_acosh;return FUNCTION;}
"atanh"              {yylval.fn = B_atanh;return FUNCTION;}
"sqrt"               {yylval.fn = B_sqrt; return FUNCTION;}
"cbrt"               {yylval.fn = B_cbrt; return FUNCTION;}
"abs"                {yylval.fn = B_abs; return FUNCTION;}
"ceil"               {yylval.fn = B_ceil; return FUNCTION;}
"floor"              {yylval.fn = B_floor; return FUNCTION;}
"erf"                {yylval.fn = B_erf; return FUNCTION;}
"tgamma"             {yylval.fn = B_tgamma; return FUNCTION;}
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
                        yyerror("Invalid sequence of characters %c",*yytext);
                    }
%%
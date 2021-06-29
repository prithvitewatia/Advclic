#include "calculator.h"
#include "colour.h"
#include <string.h>

ast* newast(int nodetype,ast* left,ast* right){
    ast* a= malloc(sizeof(ast));
    
    if(!a){
        yyerror("Out of memory\n");
        exit(EXIT_FAILURE);
    }
    a->nodetype= nodetype;
    a->l=left;
    a->r=right;
    return a;
}

ast* newnum(double d){
    numval* a=malloc(sizeof(numval));
    
    if(!a){
        yyerror("Out of memory\n");
        exit(EXIT_FAILURE);
    }
    a->nodetype = 'K';
    a->number = d;
    return (ast*)a;
}

ast* newcmp(int cmptype,ast* l,ast* r){
    ast* a = malloc(sizeof(ast));

    if(!a){
        yyerror("Out of memory");
        exit(EXIT_FAILURE);
    }
    a->nodetype = '0' + cmptype;
    a->l = l;
    a->r = r;
    return a;
}

ast* newcall(int functype,ast* explist){
    ast* a = malloc(sizeof(ast));
    
    if(!a){
        yyerror("Out of memory");
        exit(EXIT_FAILURE);
    }
    a->nodetype = functype;
    a->l = explist;
    a->r = NULL;
    return a;
}

double eval(ast* a){
    double v,t;   // Calculated value of this subtree
    char buf[50];
    
    switch (a->nodetype)
    {
    /* Constant */
    case 'K':
        v=((numval*)a)->number;
        break;
    /* Logical operations */
    case 'n':
        v = ! eval(a->l);
        break;
    case '~':
        v = ~ (int)eval(a->l);
        break;
    case '&':
        v = (int)eval(a->l) & (int)eval(a->r);
        break;
    case '|':
        v = (int)eval(a->l) | (int)eval(a->r);
    case 'x':
        v = (int)eval(a->l) ^ (int)eval(a->r);
        break;
    case 'o':
        v = eval(a->l) || eval(a->r);
        break;
    case 'a':
        v = eval(a->l) && eval(a->r);
        break;
    /* Arithmetic operations */
    case '+':
        v = eval(a->l) + eval(a->r);
        break;
    case '-':
        v = eval(a->l) - eval(a->r);
        break;
    case '*':
        v = eval(a->l) * eval(a->r);
        break;
    case '/':
        v = eval(a->l) / eval(a->r);
        break;
    case '%':
        v = (int)eval(a->l) % (int)eval(a->r);
        break;
    case 'M':
        v = -eval(a->l);
        break;
    case '^':
        v = pow(eval(a->l),eval(a->r));
        break;
    /* comparisons */
    case '1':
        v = eval(a->l) > eval(a->r) ? 1:0;
        break;
    case '2':
        v = eval(a->l) < eval(a->r) ? 1:0;
        break;
    case '3':
        v = eval(a->l) != eval(a->r) ? 1:0;
        break;
    case '4':
        v = eval(a->l) == eval(a->r) ? 1:0;
        break;
    case '5':
        v = eval(a->l) >= eval(a->r) ?1:0;
        break;
    case '6':
        v = eval(a->l) <= eval(a->r) ? 1:0;
        break;
    /* evaluating the functions
       All function evaluations will use a temp variable
       t to store to evaluation of explist
    */
    case B_exp:
        t = eval(a->l);
        v = exp(t);
        break;
    case B_exp2:
        t = eval(a->l);
        v =exp2(t);
        break;
    case B_log:
        t = eval(a->l);
        v = log(t);
        break;
    case B_log2:
        t = eval(a->l);
        v = log2(t);
        break;
    case B_log10:
        t = eval(a->l);
        v = log10(t);
        break;
    case B_cos:
        t = eval(a->l);
        v = cos(t);
        break;
    case B_sin:
        t = eval(a->l);
        v = sin(t);
        break;
    case B_tan:
        t = eval(a->l);
        v = tan(t);
        break;
    case B_asin:
        t = eval(a->l);
        v = asin(t);
        break;
    case B_acos:
        t = eval(a->l);
        v = acos(t);
        break;
    case B_atan:
        t = eval(a->l);
        v = atan(t);
        break;
    case B_sinh:
        t = eval(a->l);
        v = sinh(t);
        break;
    case B_cosh:
        t = eval(a->l);
        v = cosh(t);
        break;
    case B_tanh:
        t = eval(a->l);
        v = tanh(t);
        break;
    case B_asinh:
        t = eval(a->l);
        v = asinh(t);
        break;
    case B_acosh:
        t = eval(a->l);
        v = acosh(t);
        break;
    case B_atanh:
        t = eval(a->l);
        v = atanh(t);
        break;
    case B_sqrt:
        t = eval(a->l);
        v = sqrt(t);
        break;
    case B_cbrt:
        t = eval(a->l);
        v = cbrt(t);
    case B_abs:
        t = eval(a->l);
        v = abs(t);
        break;
    case B_ceil:
        t = eval(a->l);
        v = ceil(t);
        break;
    case B_floor:
        t = eval(a->l);
        v = floor(t);
        break;
    case B_erf:
        t = eval(a->l);
        v = erf(t);
        break;
    case B_tgamma:
        t = eval(a->l);
        v = tgamma(t);
        break;
    default:
        sprintf(buf,"Internal error: bad node %c",a->nodetype);
        printCOLOUR("red",buf);
    }
    return v;
}

void treefree(ast* a){
    char buf[50];
    switch (a->nodetype)
    {
    /* two subtrees */
    case '+': case '-': case '*': case '/': case '%':
    case '0': case '1': case '2': case '3': case '4': 
    case '5': case '6': case '|': case '&': case 'x':
    case 'o': case 'a': case '^':
        treefree(a->r);
    /* One subtree */
    case 'M':
    case 'n':
    case '~':
    /* freeing functions */
    case B_exp: case B_exp2: case B_log:
    case B_log2: case B_log10: case B_cos:
    case B_sin: case B_tan: case B_asin:
    case B_acos: case B_atan: case B_sinh:
    case B_cosh: case B_tanh: case B_asinh:
    case B_acosh: case B_atanh: case B_sqrt:
    case B_cbrt: case B_abs: case B_ceil:
    case B_floor: case B_erf: case B_tgamma:
        treefree(a->l);
    /* no subtree */
    case 'K':
        free(a);
        break;
    default:
        sprintf(buf,"Internal error: bad node %c",a->nodetype);
        printCOLOUR("red",buf);
    }
}

void yyerror(char* s,...){
    va_list ap;
    va_start(ap,s);
    
    fprintf(stderr,"\033[0;31m");    // setting the colour code of stderr to red
    fprintf(stderr,"Error in line %d\n",yylineno);  // Printing error line number
    vfprintf(stderr,s,ap);  //Printing the error message
    fprintf(stderr,"\n\033[0m");    //Resetting the colour code
}

void help(){
    char* help_msg="Calculator\n"
    "Copyright (c) 2021 Prithvi\n"
    "Permission is hereby granted, free of charge, to any person obtaining "
    "a copy of this software and associated documentation files (the "
    "'Software'), to deal in the Software without restriction, including "
    "without limitation the rights to use, copy, modify, merge, publish,"
    "distribute, sublicense, and/or sell copies of the Software, and to "
    "permit persons to whom the Software is furnished to do so, subject to "
    "the following conditions:\n\n"

    "The above copyright notice and this permission notice shall be "
    "included in all copies or substantial portions of the Software.\n\n"

    "THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,"
    "EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF "
    "MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND "
    "NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE "
    "LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION "
    "OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION "
    "WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.\n\n"
    "AUTHOR:Prithvi\n"
    "Operators supported:\n"
    "Addition: +,Subtraction: -,Multiplication: *,Division: /, Modulation %,Power ^\n"
    "Logical Opeartors:\n"
    "And: and , Or: or, Xor: xor,Not: not,Bitwise AND: &, Bitwise OR: |,Bitwise Not: ~\n"
    "Functions:\n"
    "exp(x): Returns e to the power x\n"
    "exp2(x): Returns 2 to the power x\n"
    "log(x): Returns logarithm of x to the base e\n"
    "log2(x): Returns logarithm of x to the base 2\n"
    "log10(x): Returns logarithm of x to the base 10\n"
    "cos(x): Returns cosine of x\n"
    "sin(x): Returns sine of x\n"
    "tan(x): Returns tangent of x\n"
    "acos(x): Returns arc of cos x or cos inverse x\n"
    "asin(x): Returns arc of sin x or sin inverse x\n"
    "atan(x): Returns arc of tan x or tan inverse x\n"
    "sinh(x): Returns hyperbolic sine of x\n"
    "cosh(x): Returns hyperbolic cosine of x\n"
    "tanh(x): Returns hyperbolic tangent of x\n"
    "asinh(x):Returns arc of hyperbolic sine of x\n"
    "acosh(x):Returns arc of hyperbolic cosine of x\n"
    "atanh(x):Returns arc of hyperbolic tangent of x\n"
    "sqrt(x):Returns square root of x\n"
    "cbrt(x): Returns cube root of x\n"
    "abs(x): Returns absolute value of x\n"
    "ceil(x): Returns ceil of x\n"
    "floor(x): Retruns floor of x\n"
    "erf(x): erf x is the probability that Y falls in the range [-x,x]\n"
    "tgamma(x): The gamma function\n";

    printCOLOUR("yellow",help_msg);
    printCOLOUR("blue","[Expr]");
}

int main(){
    const char* version="2.0.0";
    char* welcome_message="Welcome to the calculator utility.\n"
                        "Type h for help or q for quit\n";
    
    char version_info[50];
    sprintf(version_info,"Version=%s\n",version);
    printCOLOUR("cyan",version_info);
    printCOLOUR("yellow",welcome_message);  // Printing Welcome message in yellow
    printCOLOUR("blue","[Expr]"); //Displaying expression prompt in Blue
    return yyparse();
}
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

double eval(ast* a){
    double v;   // Calculated value of this subtree
    char buf[50];
    
    switch (a->nodetype)
    {
    case 'K':
        v=((numval*)a)->number;
        break;
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
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
        treefree(a->r);
    case 'M':
        treefree(a->l);
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
    "Copyright (c) 2012-2021 Scott Chacon and others\n"
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
    "Full Documentation: link/to/documentation/to/be/added/soon\n"
    "Operators supported:\n"
    "Addition: +\n"
    "Subtraction: -\n"
    "Multiplication: *\n"
    "Division: /\n"
    "Modulation: % (warning operands are cast into integers)\n";

    printCOLOUR("yellow",help_msg);
    printCOLOUR("blue","[Expr]");
}

int main(){
    const char* version="1.0.2";
    char* welcome_message="Welcome to the calculator utility.\n"
                        "Type h for help or q for quit\n";
    
    char version_info[50];
    sprintf(version_info,"Version=%s\n",version);
    printCOLOUR("cyan",version_info);
    printCOLOUR("yellow",welcome_message);  // Printing Welcome message in yellow
    printCOLOUR("blue","[Expr]"); //Displaying expression prompt in Blue
    return yyparse();
}
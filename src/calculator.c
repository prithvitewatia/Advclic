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
        printf("\033[0;31m");    //Setting the output colour to red
        printf("Internal error: bad node %c\n",a->nodetype);    //Displaying the error message
        printf("\033[0m");  // Resetting the colour
    }
    return v;
}

void treefree(ast* a){
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
        printf("\033[0;31m");    // Setting the output colour to red
        printf("Internal error: bad node %c\n",a->nodetype);    // Displaying the error message
        printf("\033[0m");  // Resetting the colour
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
    char* help_msg="This is the help message\n";
    printCOLOUR("\033[0;33m",help_msg);
    printCOLOUR("\033[0;34m","[Expr]");
}

int main(){
    char* welcome_message="Welcome to the calculator utility.\n"
                        "Type h for help or q for quit";
    const char* version="1.0.1";
    printf("\033[1;36mVersion=%s\n\033[0m",version);
    printCOLOUR("\033[0;33m",welcome_message);  // Printing Welcome message in yellow
    printCOLOUR("\033[0;34m","[Expr]"); //Displaying expression prompt in Blue
    return yyparse();
}
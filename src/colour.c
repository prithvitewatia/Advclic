#include "colour.h"

void printCOLOUR(const char* colour,const char* msg){
    printf("%s",colour);
    printf("%s",msg);
    puts("\033[0m");    // Resetting the colour
}
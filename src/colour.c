#include "colour.h"

void printCOLOUR(const char* colour,const char* msg){
    #ifdef _WIN32
        #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
        #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
        #endif
        // Set output mode to handle virtual terminal sequences
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut == INVALID_HANDLE_VALUE)
        {
            GetLastError();
        }

        DWORD dwMode = 0;
        if (!GetConsoleMode(hOut, &dwMode))
        {
            GetLastError();
        }

        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        if (!SetConsoleMode(hOut, dwMode))
        {
            GetLastError();
        }
    #endif
    // Setting the terminal to the corresponding colour
    if(strcmp(colour,"red")==0){
        printf("\033[0;31m");
    }
    else if(strcmp(colour,"green")==0){
        printf("\033[0;32m");
    }
    else if(strcmp(colour,"yellow")==0){
        printf("\033[0;33m");
    }
    else if(strcmp(colour,"blue")==0){
        printf("\033[0;34m");
    }
    else if(strcmp(colour,"cyan")==0){
        printf("\033[0;36m");
    }
    printf("%s",msg);
    printf("\033[0m");
}
#include "stdio.h"

#include "fileManager.h"

#define line "---------------------------------------------------------------------------------------------------------\n"  //serve per il printf


void start(short mode);


/**
 *  The main function of this application reads the first word of a txt file,
 *      cyphers it and create another as output (if the file to create already exists,
 *          it will be overwrited).
 */
int main()
{
    short exit = 0;
    while(exit == 0) {
        printf(line"scegli un'opzione:\n0-interrompi programma       1-cifra il testo       2-decifra il testo\n"line);
        int selection;
        scanf("%d", &selection);
        switch (selection) {
            case 0: {exit=1; continue;}
            case 1: {start(1); continue;}
            case 2: {start(-1); continue;}
            default: {printf("inserire un numero compreso tra 0 e 2\n");}
        }
    }
}
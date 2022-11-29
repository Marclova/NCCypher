#include "NCCypher.h"

#define inputPath "/home/redh/Desktop/CLionProjects/NCCypherProject/cmake-build-debug/input.txt"  //full path del file input
#define outputPath "/home/redh/Desktop/CLionProjects/NCCypherProject/cmake-build-debug/output.txt"  //full path del file output
#define myMacAddr "00:0c:29:2c:61:79"

long getFileSize();

char macAddress[17] = myMacAddr;

/**
 *  Questa funzione fa partire il cifratore, sia per cifrare che per decifrare
 *
 * @param mode   determina se cifrare (mode==1) o decifrare (mode==-1)
 */
void start(short mode) {      //questa funzione non rispetta il principio DRY a causa di problemi con le chiamate
    //FILE *macAddr = fopen("/sys/class/net/ens33/address.txt","r");        //non lo uso perché questo programma non è autorizzato a leggere questo file
    //fscanf(macAddr,"%s",macAddress);
    setCypherWithMacAddress(macAddress);
    FILE *inputFile = fopen(inputPath, "r");
    long textSize = getFileSize(inputPath);      //ottengo la dimensione del messaggio per poi assegnare il valore alla costante che lo conterrà
    char textRead[textSize];
    fread(textRead,textSize,textSize,inputFile);
    printf("la frase rilevata è:\n");
    for(int i=0; i<textSize; i++)
    {
        printf("%c",textRead[i]); //scrivo il messaggio originale, un carattere alla volta
        textRead[i] = cypherOneCharacter(textRead[i], mode);  //cifra ogni carattere uno alla volta
    }
    if (mode==1) {printf("\nla frase criptata è:\n");}
    else {printf("\nla frase decriptata è:\n");}
    printf("%s\n\n", textRead);
    FILE *outputFile = fopen(outputPath, "w");    //scrivo il risultato nel file "output.txt"
    fprintf(outputFile, textRead),
            fclose(inputFile);
    fclose(outputFile);
}

/**
 * Funzione che calcola le dimensioni di un char array
 *
 * @param dir Full path of the directory
 *
 * @return
 */
long getFileSize(char dir[]) {
    FILE *f = fopen(dir, "r");
    fseek(f,0l,SEEK_END);
    return ftell(f)-1;
}
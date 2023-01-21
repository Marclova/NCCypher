#include "NCCypher.h"

#include "MacAddressProvider.h"

#define inputPath "input.txt"  //relative path del file input
#define outputPath "output.txt"  //relative path del file output
//#define myMacAddr "00:0c:29:2c:61:79"

long getFileSize();

//char macAddress[17] = myMacAddr;

/**
 *  Questa funzione fa partire il cifratore, sia per cifrare che per decifrare
 *
 * @param mode   determina se cifrare (mode==1) o decifrare (mode==-1)
 */
void start(short mode) {      //questa funzione non rispetta il principio DRY a causa di problemi con le chiamate
    char myMacAddr[17];
    getMacAddress(myMacAddr);
    printf("il tuo indirizzo MAC è: %s\n",myMacAddr);
    setCypherWithMacAddress(myMacAddr);

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
    if (mode==1) {printf("\nla frase cifrata è:\n");}
    else {printf("\nla frase decifrata è:\n");}
    printf("%s\n\n", textRead);
    FILE *outputFile = fopen(outputPath, "w");    //scrivo il risultato nel file "output.txt"
    fprintf(outputFile, textRead);
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
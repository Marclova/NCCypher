#include "stdio.h"

short counterMod5;      //insieme all'altro contatore genera "thisflag" ad ogni iterazione
short counterMod7;      //insieme all'altro contatore genera "thisflag" ad ogni iterazione
short thisFlag;     //insieme a "previousFlag" determina come incrementare "increaseCounter"
short previousFlag;     //insieme a "previousFlag" determina come incrementare "increaseCounter"
short charSwifter;     //il contatore che effettivamente determina la traslazione dei caratteri

void incrementCounters();
void actualCalculator();

/**
 *  This function uses the actual calculator in order to set the value of the charSwifter and then use it to
 *      cypher a single character
 *
 * @param c     The character to cypher.
 * @param mode  This value is equal 1 when cyphering and -1 when deciphering
 *
 * @return      The cyphered character.
 */
char cypherOneCharacter(char c, short mode)
{
    if(c=='\n')     //se il carattere l'etto è un backslash. esso verrà ignorato
    {
        printf("%c",c);
        return c;
    }
    actualCalculator();
    c += (charSwifter * mode);
    return c;
}


/**
 * This function increases the counters and updates the flags
 */
void actualCalculator() {
    thisFlag = (short)((counterMod5 + counterMod7)%2);  //aggiorno "thisFlag" in base al valore attuale dei contatori
    incrementCounters();    //aggiorno i contatori in base al valore di "thisFlag" e "previousFlag"
    previousFlag = thisFlag;    //aggiorno "previousFlag" con il valore di "thisFlag"
}


/**
 * This function increments the three counters of the cypher using a relatively complex algorithm in order to be
 *      hardly predictable
 */
void incrementCounters() {
    if(counterMod5++ == 4) {counterMod5 = 0;}
    if(counterMod7++ == 6) {counterMod7 = 0;}
    if (thisFlag == 0)  //a ogni iterazione si controlla il valore del flag e se è cambiato rispetto all'iterazione precedente
    {
        if (previousFlag == 0)  //per ogni "0" nella serie consecutiva il counter aumenta
        {
            charSwifter++;
        }
        else
        {
            charSwifter = 1;  //finita la serie consecutiva di "1" il counter viene impostato ad 1
        }
    }
    else
    {
        if (previousFlag == 1)  //per ogni "1" nella serie consecutiva il counter aumenta
        {
            charSwifter += 2;
        }
        else
        {
            charSwifter = 2;  //finita la serie consecutiva di "0" il counter viene impostato ad 1
        }
    }
    if (charSwifter == 7) {charSwifter = 1;}    //evito che il contatore diventi troppo grande per la tabella ASCII
    if (charSwifter >= 10) {charSwifter = 4;}
}

/**
 * This function resets all the parameters of the cypher, then it sets the starting values of the two modular counters
 *      depending on the mac address inserted (address format: "xx:xx:xx:xx:xx:xx")
 *
 * @param mac The mac to use as cypher key
 */
void setCypherWithMacAddress(char mac[17]) {
    counterMod5 = 0;
    counterMod7 = 0;
    thisFlag = 0;
    previousFlag = 0;
    charSwifter = 0;
    for(short i=0; i<17; i+=3)   //faccio salti di tre per leggere ogni volta la prima e la seconda cifra dei 6 numeri dell'indirizzo mac
    {
        short increaseMod5 = mac[i];
        short increaseMod7 = mac[i+1];
        counterMod5 += increaseMod5;
        counterMod7 += increaseMod7;
        while (counterMod5 >= 5)
            counterMod5 -= 5;       //mantengo i valori all'interno dei moduli 5 e 7
        while (counterMod7 >= 7)
            counterMod7 -= 7;
    }
}
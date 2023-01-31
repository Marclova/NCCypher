#include <stdio.h>
#include <string.h>
#include <net/if.h>
#include <ifaddrs.h>
#include <netpacket/packet.h>


void getMacAddress(char *mac_address) {
    struct ifaddrs *ifaddr;       //Creo le due struct che conterranno i dati delle interfacce

    if (getifaddrs(&ifaddr) == -1) {    //il metodo crea una lista collegata di struct ifaddrs, inizializzando *ifaddr
        perror("Error getting interfaces");
        return;
    }

    while (1==1)
    {
        ifaddr = ifaddr->ifa_next;      //iterazione su tutte le interfacce
        if (ifaddr == NULL)      //se l'interaffia corrrente Non contiene un indirizzo, allora si è arrivati alla fine dell'iterazione
            break;
        if ((ifaddr->ifa_flags & IFF_UP) && (ifaddr->ifa_addr->sa_family == AF_PACKET)) {     //controllo se l'interfaccia è attiva ed è un AF_PACKET
            char *interface_name = ifaddr->ifa_name;
            if (interface_name[0] == 'e' || interface_name[0] == 'w') {
                struct sockaddr_ll *s = (struct sockaddr_ll*)ifaddr->ifa_addr;     //cast da iffadrs a sockaddr_ll
                for (int i = 0; i < 6; i++) {        //estrazione del valore MAC un byte alla volta...
                    sprintf(mac_address+i*3, "%02X:", s->sll_addr[i]);  //...perché è necessario costruire una sringa
                }
                mac_address[strlen(mac_address)-1] = '\0';  //rimozione dell'ultimo carattere ":"
                break;
            }
        }
    }
}
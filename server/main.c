#ifndef TEST_H
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>


#include "../structure/structures.h"

#define PORT 3490
#endif


// include files



/*
    * Function: requestManager()
    * ----------------------------
    *  This function is used to manage the requests.
    *  It will receive the request and send it to the server.
    */
   
void *requestManager()
{

    int sock, lg;
    struct sockaddr_in adr_s, adr_c;
    lg = sizeof(adr_c);
    struct request buffer;

    //Socket creation
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // Creation socket
    bzero(&adr_s, sizeof(adr_s));
    adr_s.sin_family = AF_INET;
    adr_s.sin_port = htons(PORT);
    adr_s.sin_addr.s_addr = htonl(INADDR_ANY);

    //attach socket to the server
    if (bind(sock, (struct sockaddr *) &adr_s, sizeof(adr_s)) < 0)
    {
        perror("connect");
    }

    while (1)
    {
        // ATTENTE D'UN MESSAGE
        if (recvfrom(sock, &buffer, sizeof(buffer), 0, (struct sockaddr *) &adr_c, &lg))
        {
            printf("  --- Before start real REQUEST MANAGER --- Message reçu :");
            // réception du message dans le &buffer

            switch (buffer.action)
            {
            case 0:
                printf(" --- REQUEST MANAGER --- Connexion de l'utilisation \n");
                // log in
                break;
            case 1:
                printf(" --- REQUEST MANAGER --- Déconnexion de l'utilisation \n");
                // log out
                break;
            case 2:
                printf(" --- REQUEST MANAGER --- Création d'un compte \n");
                // create account
                break;
            case 3:
                printf(" --- REQUEST MANAGER --- Suppression d'un compte \n");
                // delete account
                break;
            default:
                printf(" --- REQUEST MANAGER --- Action inconnue \n");
                //do nothing
                break;
            }
        }
    }
}


int main(int argc, char const *argv[])
{
  return 0;

}


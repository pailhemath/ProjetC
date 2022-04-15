#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include "structures.h"
#include <stdlib.h>
#include <pthread.h>
#define PORT 3004

int STATE = 0;


//gcc -g -pthread server.c -o server


int decodeBuffer( char buffer[100]){
   
    if(strcmp(buffer, "-help\n") == 0){
        return 999999;
    }else if(strcmp(buffer, "-create\n") == 0){
        return 999998;
    }else if(strcmp(buffer, "-delete\n") == 0){
        return 999997;
    }else if(strcmp(buffer, "-login\n") == 0){
        return 999996;
    }else if(strcmp(buffer, "-logout\n") == 0){
        return 999995;
    }else if(strcmp(buffer, "-list\n") == 0){
        return 999994;
    }else if(strcmp(buffer, "-quit\n") == 0){
        return 999993;
    }else
        return 0;
}




/*
    * Function: requestManager()
    * ----------------------------
    *  This function is used to manage the requests.
    *  It will receive the request and send it to the server.
    */
void *requestManager()
{

    int sock, lg, decode;
    struct sockaddr_in adr_s, adr_c;
    lg = sizeof(adr_c);
    //struct request buffer;
    char buffer[100];

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

    while (STATE == 0)
    {
        // ATTENTE D'UN MESSAGE
        if (recvfrom(sock, &buffer, sizeof(buffer), 0, (struct sockaddr *) &adr_c, &lg))
        {
            //printf("  --- Before start real REQUEST MANAGER --- Message reçu :");
            // réception du message dans le &buffer
            //printf(" \n------------\n %s\n------------\n", buffer);
            //int message = atoi(buffer);
            //transforme buffer to string
            decode = decodeBuffer(buffer);
            switch (decode)
            {

            case 999996:
                printf("REQUEST-MANAGER Connexion de l'utilisation \n");
                // log in
                break;
            case 999993:
                printf("REQUEST-MANAGER Déconnexion de l'utilisation \n");
                // log out
                break;
            case 999998:
                printf("REQUEST-MANAGER Création d'un compte \n");
                // create account
                break;
            case 999997:
                printf("REQUEST-MANAGER Suppression d'un compte \n");
                // delete account
                break;
            case 999994:
                printf("REQUEST-MANAGER Liste des comptes \n");
                // list accounts
                break;
            case 0:
                printf("REQUEST-MANAGER Action inconnue \n");
                //do nothing
                //STATE = 1;
                break;
            default:
                printf("REQUEST-MANAGER IL Y A UN GROS PROBLEME \n");
                //do nothing
                //STATE = 1;
                break;
            }
        }
    }
}



int main()
{
    // create a thread
    pthread_t t1;


    //call a thread
    pthread_create(&t1, NULL, &requestManager, NULL /* args*/ );
    pthread_join(t1, NULL /* get result from thread */ );

    return 0;
}

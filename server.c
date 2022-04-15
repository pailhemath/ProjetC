#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include "structures.h"

#define PORT 2058



int main()
{
    // serveur
    int sock, lg;
    struct sockaddr_in adr_s, adr_c;
    lg = sizeof(adr_c);
    int buffer;

    /* but transformer le buffer en structure de type request */

    
    // Socket creation
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // Creation socket
    bzero(&adr_s, sizeof(adr_s));
    adr_s.sin_family = AF_INET;
    adr_s.sin_port = htons(PORT);
    adr_s.sin_addr.s_addr = htonl(INADDR_ANY);

    // attach socket to the server
    if (bind(sock, (struct sockaddr *)&adr_s, sizeof(adr_s)) < 0)
    {
        perror("connect");
    }

    while (1)
    {
        // ATTENTE D'UN MESSAGE
        if (recvfrom(sock, &buffer, sizeof(buffer), 0, (struct sockaddr *)&adr_c, &lg))
        {
            printf("  --- Before start real REQUEST MANAGER --- Message reçu :");
            // réception du message dans le &buffer

            switch (buffer)
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
            case 4:
                printf(" --- REQUEST MANAGER --- Afficher les personnes connectés \n");
                // display all users
                break;
            default:
                printf(" --- REQUEST MANAGER --- Action inconnue \n");
                // do nothing
                break;
            }
        }
    }
}

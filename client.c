
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include "structures.h"
 
#define PORT 3004

void printHelp(){
    printf("Bienvenue dans le programme de gestion de compte.\n");
    printf(" -help : Affiche l'aide\n");
    printf(" -create : Crée un compte\n");
    printf(" -delete : Supprime un compte\n");
    printf(" -login : Se connecte\n");
    printf(" -logout : Se déconnecte\n");
    printf(" -list : Affiche la liste des comptes\n");
    printf(" -quit : Quitte le programme\n");
}

int main()
{ // client
    int sock;
    char buf[50];
    struct sockaddr_in adr_s, adr_c;
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // Creation socket
    bzero(&adr_c, sizeof(adr_c));
    adr_c.sin_family = AF_INET;
    adr_c.sin_port = htons(PORT);
    adr_c.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(sock, (struct sockaddr *)&adr_c, sizeof(adr_c)); // Attachement socket
    bzero(&adr_s, sizeof(adr_s));
    adr_s.sin_family = AF_INET;
    adr_s.sin_port = htons(PORT);
    adr_s.sin_addr.s_addr = htonl(INADDR_ANY);
        /* Establish the connection */
    if ((connect(sock ,(struct sockaddr *)&adr_s,sizeof(adr_s))) == -1 ) {
        perror("Connection to socket failed");

    }else{
        printHelp();
    }

    while(1)
    {
        //if user press enter
        if(fgets(buf, 20, stdin) != NULL)
        {
            //if buff == "-help
            if(strcmp(buf, "-help\n") == 0)
            {
                printHelp();
            }else
            sendto(sock, buf, 20, 0, (struct sockaddr *)&adr_s, sizeof(adr_s));
        }
        
    }
    //close(sock);
}

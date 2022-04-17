#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include "structures.h"
#include "fonctions.c"

#define PORT 3004

void printHelp() {
    printf("Bienvenue dans le programme de gestion de compte.\n");
    printf(" -help : Affiche l'aide\n");
    printf(" -create : Crée un compte\n");
    printf(" -delete : Supprime un compte\n");
    printf(" -login : Se connecte\n");
    printf(" -logout : Se déconnecte\n");
    printf(" -list : Affiche la liste des comptes\n");
    printf(" -quit : Quitte le programme\n");
}

int EnvoieFileMessage() {
    key_t cle;
    int msgid, i;
    requete req;
    reponse rep;
    // On recherche la file de message
    if ((cle = ftok(SERVEUR, '0')) == -1) {
        fprintf(stderr, "Obtention de la cle impossible. Fin du serveur.\n");
        exit(EXIT_FAILURE);
    }
    if ((msgid = msgget(cle, 0)) == -1) {
        fprintf(stderr, "Erreur: file inconnue. Fin du client.\n");
        exit(EXIT_FAILURE);
    }
    //
    printf("Client operationnel\n");
    req.type = 1L;
    req.signature = getpid();
    while (1) {
        printf("--> ");
        fgets(req.chaine, TAILLE_REP, stdin);
        req.chaine[strlen(req.chaine) - 1] = '\0';
        if (strlen(req.chaine) == 0) continue;
        if (strcmp(req.chaine, "exit") == 0) {
            printf("Au revoir !\n");
            exit(EXIT_SUCCESS);
        }
        printf("Requete de %d envoyee: ->%s<-\n", req.signature, req.chaine);
        if (msgsnd(msgid, &req, TAILLE_REQ, 0) == -1) {
            fprintf(stderr, "%d: erreur d'envoi de la requete %s au serveur\n", req.signature, req.chaine);
            fprintf(stderr, "Fin du client %d.\n", req.signature);
            exit(EXIT_FAILURE);
        }
        if (msgrcv(msgid, &rep, TAILLE_REP, (long) req.signature, 0) == -1) {
            fprintf(stderr, "%d: erreur de reception de la reponse du serveur.\n", req.signature);
            fprintf(stderr, "Fin du client %d.\n", req.signature);
            exit(EXIT_FAILURE);
        }
        printf("%d: reponse du serveur ->%s<-\n", req.signature, rep.chaine);
        int decode = decodeBuffer(rep.chaine);
        switch (decode) {

            case 999996:
                printf("REQUEST-MANAGER Connexion de l'utilisation \n");
                // log in
                int shmid = connexion();
                break;
            case 999993:
                printf("REQUEST-MANAGER Déconnexion de l'utilisation \n");
                // log out
                break;
            case 999998:
                printf("REQUEST-MANAGER Création d'un compte \n");
                // create account
                inscription();
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

int main() { // client
    int sock;
    char buf[50];
    struct sockaddr_in adr_s, adr_c;
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // Creation socket
    bzero(&adr_c, sizeof(adr_c));
    adr_c.sin_family = AF_INET;
    adr_c.sin_port = htons(PORT);
    adr_c.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(sock, (struct sockaddr *) &adr_c, sizeof(adr_c)); // Attachement socket
    bzero(&adr_s, sizeof(adr_s));
    adr_s.sin_family = AF_INET;
    adr_s.sin_port = htons(PORT);
    adr_s.sin_addr.s_addr = htonl(INADDR_ANY);
    // Establish the connection
   if ((connect(sock, (struct sockaddr *) &adr_s, sizeof(adr_s))) == -1) {
        perror("Connection to socket failed");

    } else {
        printHelp();
    }

    //close(sock);
    EnvoieFileMessage();
}

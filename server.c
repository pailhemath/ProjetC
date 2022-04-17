#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include "structures.h"
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "fonctions.c"

#define PORT 3004

int STATE = 0;
int msgid;


//gcc -g -pthread server.c -o server



/*
    * Function: requestManager()
    * ----------------------------
    *  This function is used to manage the requests.
    *  It will receive the request and send it to the server.
    */
/*void *requestManager() {

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
    if (bind(sock, (struct sockaddr *) &adr_s, sizeof(adr_s)) < 0) {
        perror("connect");
    }

    while (STATE == 0) {
        // ATTENTE D'UN MESSAGE
        if (recvfrom(sock, &buffer, sizeof(buffer), 0, (struct sockaddr *) &adr_c, &lg)) {
            //printf("  --- Before start real REQUEST MANAGER --- Message reçu :");
            // réception du message dans le &buffer
            //printf(" \n------------\n %s\n------------\n", buffer);
            //int message = atoi(buffer);
            //transforme buffer to string
            decode = decodeBuffer(buffer);
            switch (decode) {

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
}*/

void fin(int n) {
    fprintf(stderr, "Terminaison du serveur.\n");
    msgctl(msgid, IPC_RMID, NULL);
    exit(EXIT_SUCCESS);
}

void *requestManager() {
    key_t cle;
    struct sigaction action;
    requete req;
    reponse rep;
    int sig, i, tmp;

    // on commence par prevoir la terminaison sur signal du serveur
    action.sa_handler = fin;
    for(i=1; i<NSIG; i++) sigaction(i, &action, NULL);	// installation du handler de fin pour tous les signaux
    // creation de la file de message
    if ((cle = ftok(SERVEUR, '0')) == -1) {
        fprintf(stderr, "Obtention de la cle impossible. Fin du serveur.\n");
        exit(EXIT_FAILURE);
    }
    if ((msgid = msgget(cle, IPC_CREAT|IPC_EXCL|DROITS)) == -1) {
        fprintf(stderr, "Creation de la file impossible. Fin du serveur.\n");
        exit(EXIT_FAILURE);
    }
    // attente d'une requete a l'infini...
    while(1) {
        if (msgrcv(msgid, &req, TAILLE_REQ, 1L, 0) == -1) {
            fprintf(stderr, "Serveur: Erreur de reception de requete\n");
            continue;
        }
        printf("Serveur: requete ->%s<- du processus %d\n", req.chaine, req.signature);
        // construction de la reponse
        rep.type = req.signature;
        tmp = strlen(req.chaine);
        for(i=0; i<tmp; i++) {
            rep.chaine[i] = req.chaine[i];
        }
        rep.chaine[tmp] = '\0';
        printf("Serveur: rep.chaine ->%s<-\n", rep.chaine);
        // envoi de la reponse
        if (msgsnd(msgid, &rep, TAILLE_REP, 0) == -1) {
            fprintf(stderr, "Serveur: Erreur d'envoi d'une réponse a %d\n", req.signature);
        }
        else {
            printf("Serveur: reponse envoyee a %d\n", req.signature);
        }
    }
}

int main() {
    // create a thread
   pthread_t t1;


    //call a thread
    pthread_create(&t1, NULL, &requestManager, NULL /* args*/ );
    pthread_join(t1, NULL /* get result from thread */ );

   // return 0;
}

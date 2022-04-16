#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <unistd.h>

#define DROITS 0640
#define NB_CHAR 1024
#define SERVEUR "./serveur"
#define TAILLE_REQ (NB_CHAR+sizeof(int))
#define TAILLE_REP (NB_CHAR)

typedef struct {
    long type;
    char chaine[NB_CHAR];
    int signature;
} requete;

typedef struct {
    long type;
    char chaine[NB_CHAR];
} reponse;


struct request
{
    /*
    0 : log in
    1 : log out
    2 : create account
    3 : delete account
    */
    int action;
    char data[100]; //Data sent with request
};
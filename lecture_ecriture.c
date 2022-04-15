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
#define CLE 217

void inscription(FILE* fichier);
void connexion(FILE* fichier);

void inscription(FILE* fichier){
    char pseudo[100];
    char buf[100];
    char mdp[100];
    int cmp = 1;
    int check = 0;

    printf("Entrez votre pseudo :\n");
    scanf("%s", pseudo);
    printf("Entrez votre mot de passe :\n");
    scanf("%s", mdp);

    while (fgets(buf,30,fichier) != NULL)
    {
        char *p = strchr(buf, '\n');
        if (p != NULL)
        {
            *p = 0;
        }
        if (strcmp(buf, pseudo) == 0)
        {
            cmp = 0;
        }
    }
    if (cmp == 0){
        printf("Pseudo déjà pris !\n");
    }
    else {
        fseek(fichier, 0, SEEK_END);
        fputs(pseudo, fichier);
        fprintf(fichier,"\n");
        fputs(mdp, fichier);
        fprintf(fichier,"\n");
    }
    
}

void connexion(FILE* fichier){
    char pseudo[100];
    char buf[100];
    char mdp[100];
    char bufmdp[100];
    int cmp = 1;
    int cmpmdp = 1;
    int cont = 1;
    int tmp;

    printf("Entrez votre pseudo :\n");
    scanf("%s", pseudo);
    printf("Entrez votre mot de passe :\n");
    scanf("%s", mdp);

     while (fgets(buf,30,fichier) != NULL)
    {
        char *p = strchr(buf, '\n');
        if (p != NULL)
        {
            *p = 0;
        }
        if (strcmp(buf, pseudo) == 0)
        {
            cmp = 0;
            tmp = cont;
        }
        if((cont == tmp+1)&&(strcmp(buf, mdp) == 0)){
            cmpmdp = 0;
            break;
        }
        cont += 1;
    }
    
    if (cmp == 0 && cmpmdp == 0){
        printf("Vous êtes connecté !\n");
        char* mem;
        int shmid;
        shmid = shmget ((key_t)CLE, 1000, IPC_CREAT|0750);
        mem = shmat(shmid, NULL, 0);
        strcpy(mem, pseudo);
        //Deco
        /*shmid = shmget((key_t)CLE, 0, 0);
        mem = shmat(shmid, NULL, 0);
        printf("Pseudo : %s\n", mem);*/
    }
    else {
        printf("Vous n'êtes pas connecté !\n");
    }
}

int main(){

    FILE* fichier = NULL;
    fichier = fopen("liste.txt", "r+");

    if (fichier != NULL){
        //inscription(fichier);
        connexion(fichier);
        fclose(fichier);
    }
    else{
        printf("Impossible d'ouvrir le fichier !\n");
    }
    
    return 0;
}
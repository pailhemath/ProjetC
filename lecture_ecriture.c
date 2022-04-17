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
#define CLE 1

char* mem;
int shmid;

void inscription(FILE* fichier);
int connexion(FILE* fichier);
void lecture();
void deconnexion(int shmid);

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

int connexion(FILE* fichier){
    char pseudo[100];
    char buf[100];
    char mdp[100];
    char bufmdp[100];
    int cmp = 1;
    int cmpmdp = 1;
    int cont = 1;
    int i = 1;
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
        

        while ((shmget(i, 0, 0)) != -1){
            i += 1;
        }
        shmid = shmget (i, 1000, IPC_CREAT|0660);
        mem = shmat(shmid, NULL, 0);
        strcpy(mem, pseudo);
        
    }
    else {
        printf("Vous n'êtes pas connecté !\n");
    }
    return shmid;

}

void lecture(int i){
        if (shmget(i, 0, 0) == -1)
        {
            perror("Lecture fini") ;
            exit(1) ;
        }
        else{
            shmid = shmget(i, 0, 0);
            mem = shmat(shmid, NULL, 0);
            printf("Pseudo : %s, shmid : %d \n", mem, shmid);
            i = i + 1;
            lecture(i);
        }
}

void deconnexion(int shmid){
    {
        if (shmctl(shmid,IPC_RMID,NULL) == -1)
        {
            perror("Erreur lors de la destruction") ;
            exit(1) ;
        }
    }
}

int main(){

    FILE* fichier = NULL;
    fichier = fopen("liste.txt", "r+");
    char pseudo[100] = "val";
    char** deco;

    if (fichier != NULL){
        //inscription(fichier);
        //shmid = connexion(fichier);
        deconnexion(38);
        /*shmid = shmget(1, 0, 0);
        mem = shmat(shmid, NULL, 0);
        strcpy(mem, pseudo);
        //printf("Pseudo : %s\n", mem);
        /*shmdt(mem);
        shmctl(shmid, IPC_RMID, NULL);*/
        /*shmid = shmget (1, 0, 0);
        mem = shmat(shmid, NULL, 0);
        printf("Pseudo : %s\n", mem);*/
        //strcpy(mem, pseudo);
        lecture(1);
        /*shmid = shmget(6, 0, 0);
        mem = shmat(shmid, NULL, 0);
        printf("Pseudo : %s\n", mem);*/
        fclose(fichier);
    }
    else{
        printf("Impossible d'ouvrir le fichier !\n");
    }
    
    return 0;
}
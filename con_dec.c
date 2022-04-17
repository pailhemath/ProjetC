#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

int 
creerSegment
(int size, char *name, int cle)
{

  int shmid ;  /* l'identificateur de la m\'emoire partag\'ee  */
  key_t clef ;  /* la clef associee au segment */
  char* mem;
  /* L'instruction ftok(name,(key_t) cle) permet de construire 
     une cle identifiant le segment */
  clef = ftok(name,(key_t) cle) ;
  

  /* L'instruction IPC_CREAT|IPC_EXCL|SHM_R|SHM_W permet d'indiquer 
     les droits d'acces de ce segment de memoire */

  shmid = shmget( clef,
                  size,
                  IPC_CREAT|IPC_EXCL|SHM_R|SHM_W ) ;
  if ( shmid== -1 ) 
  {
    perror("La creation du segment de memoire partage a echouee") ;
    exit(1) ;  /* on laisse tout tomber et on sort du programme */
  }
  mem = shmat(shmid, NULL, 0);
  strcpy(mem, "val");
  printf("l'identificateur du segment est %d \n",shmid) ;
  printf("ce segment est associe a la clef %d \n",clef) ;

  return shmid ;
}

void 
infoSegment
(int shmid) 
{
 struct shmid_ds buf ;

  if (shmctl(shmid,IPC_STAT,&buf) == -1)
  {
    perror("Erreur lors de l'utilsation de infoSegment") ;
    exit(1) ;
  }

  printf("Affichage des champs de controles\n") ;
  printf("identificateur du proprietaire : %d\n",buf.shm_perm.uid) ;
  printf("identificateur du groupe du proprietaire : %d\n",buf.shm_perm.gid) ;
  printf("identificateur du createur : %d\n",buf.shm_perm.cuid) ;
  printf("identificateur du groupe du createur : %d\n",buf.shm_perm.cgid) ;
  printf("mode d'acces : %d\n",buf.shm_perm.mode) ;
  printf("taille du segment : %d\n",(int) buf.shm_segsz) ;
}

void 
detruitSegment
(int shmid) 
{
 if (shmctl(shmid,IPC_RMID,NULL) == -1)
 {
    perror("Erreur lors de la destruction") ;
    exit(1) ;
 }
}

void lecture(){
    char* mem;
    int shmid;
    int i = 1;
    while ((shmget(i, 0, 0)) != -1){
        shmid = shmget(i, 0, 0);
        mem = shmat(shmid, NULL, 0);
        printf("Pseudo : %s\n", mem);
        i += 1;
    }
}

int
main
(void)
{
  int shmid ;
  char *name ;

  name = "sharedMemory.c" ;

  shmid = creerSegment(100,name,1) ;

  infoSegment(shmid) ;

  //lecture();

  detruitSegment(shmid) ;

  /*shmid = shmget( 1, 0, 0) ;
  shmctl(shmid,IPC_RMID,NULL);*/

  return 1 ;
}
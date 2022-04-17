#include "fonctions.h"

#define FILENAME_SIZE 1024
#define MAX_LINE 2048


//void end_program (GtkWidget *wid, gpointer ptr);


//GtkWidget *txt;
//GtkWidget *txt2;
char pseudo[100];
char mdp[100];
#define CLE 217




void connexion(){
    char buf[100];
    char bufmdp[100];
    int cmp = 1;
    int cmpmdp = 1;
    int cont = 1;
    int tmp;
    FILE* fichier = NULL;
    fichier = fopen("liste.txt", "r+");

       /* void copy_text (GtkWidget *wid, gpointer ptr)
    {
        strcpy(pseudo,gtk_entry_get_text(GTK_ENTRY(txt)));
        strcpy(mdp,gtk_entry_get_text(GTK_ENTRY(txt2)));
        end_program(wid, ptr);
         gtk_widget_destroy(wid);
        
    }*/
    printf("Entrez votre pseudo :\n");
    scanf("%s", pseudo);
    printf("Entrez votre mot de passe :\n");
    scanf("%s", mdp);
    //print pseudo and mdp


   /* gtk_init (NULL, NULL);
    GtkWidget *win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    g_signal_connect (win, "delete_event", G_CALLBACK (end_program),NULL);
    GtkWidget *lbl = gtk_label_new ("username :");
    GtkWidget *lbl2 = gtk_label_new ("password :");
    GtkWidget *btn2 = gtk_button_new_with_label ("Se Connecter");
    g_signal_connect (btn2, "clicked", G_CALLBACK (copy_text), NULL);
    g_signal_connect (btn2, "clicked", G_CALLBACK (end_program), NULL);
    //G_CALLBACK (end_program)
    txt = gtk_entry_new ();
    txt2 = gtk_entry_new ();
    GtkWidget *tab = gtk_table_new (5, 2, TRUE);
    gtk_table_attach_defaults (GTK_TABLE (tab), lbl, 0, 1, 0, 1); // username :
    gtk_table_attach_defaults (GTK_TABLE (tab), txt, 1, 2, 0, 1); //zone de sélection
    gtk_table_attach_defaults (GTK_TABLE (tab), lbl2, 0, 1, 1, 2); // password :
    gtk_table_attach_defaults (GTK_TABLE (tab), txt2, 1, 2, 1, 2);
    gtk_table_attach_defaults (GTK_TABLE (tab), btn2, 1, 2, 2, 4);
    gtk_container_add (GTK_CONTAINER (win), tab);
    gtk_widget_show_all (win);
    gtk_main ();

        printf("%s\n", pseudo);
        printf("%s\n", mdp);*/


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
      /*  char* mem;
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
    fclose(fichier);
}


int decodeBuffer( char buffer[100]){
   
    if(strcmp(buffer, "-help") == 0){
        return 999999;
    }else if(strcmp(buffer, "-create") == 0){
        return 999998;
    }else if(strcmp(buffer, "-delete") == 0){
        return 999997;
    }else if(strcmp(buffer, "-login") == 0){
        return 999996;
    }else if(strcmp(buffer, "-logout") == 0){
        return 999995;
    }else if(strcmp(buffer, "-list") == 0){
        return 999994;
    }else if(strcmp(buffer, "-quit") == 0){
        return 999993;
    }else
        return 0;
}


/*
void desinscription(){
    FILE* fichier = NULL;
    fichier = fopen("liste.txt", "r+");
    FILE* file ;
    FILE* temp;
    char filename[FILENAME_SIZE];
    char temp_filename[FILENAME_SIZE];
    char buffer1[MAX_LINE],buffer2[MAX_LINE], pseudo[MAX_LINE], mdp[MAX_LINE], temp_buffer1[MAX_LINE],temp_buffer2[MAX_LINE];


    strcpy(temp_filename, "temp____");
    strcat(temp_filename, "liste.txt");

    printf("Entrez votre pseudo :\n");
    scanf("%s", pseudo);
    printf("Entrez votre mot de passe :\n");
    scanf("%s", mdp);

    file = fichier;
    temp = fopen(temp_filename,"w");

    if(temp == NULL )
    {
        printf("Error123");
    }
    bool keep_reading = true;
    do{
        fgets(buffer1,MAX_LINE,file);
        fgets(buffer2,MAX_LINE,file);

        strcpy(temp_buffer1,buffer1);
        strcpy(temp_buffer2,buffer2);
        char *p = strchr(temp_buffer1, '\n');if (p != NULL)
        {
            *p = 0;
        }
        char *q = strchr(temp_buffer2, '\n');
        if (q != NULL)
        {
            *q = 0;
        }

        if (feof(file)){
            keep_reading = false;

        }else if((strcmp(temp_buffer1,pseudo) !=0) || (strcmp(temp_buffer2,mdp)!=0 )){
            fputs(buffer1,temp);
            fputs(buffer2,temp);

        }

    }while(keep_reading);
    fclose(file);
    fclose(temp);

    remove("liste.txt");
    rename(temp_filename,"liste.txt");

}
*/

   /* void end_program (GtkWidget *wid, gpointer ptr)
    {
        gtk_main_quit ();
    }
*/
void inscription(){
    char pseudo[100];
    char buf[100];
    char mdp[100];
    int cmp = 1;
    int check = 0;
    FILE* fichier = NULL;
    fichier = fopen("liste.txt", "r+");
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
    fclose(fichier);
    
}
/*
void fin(int n) {
    int msgid;
    fprintf(stderr, "Terminaison du serveur.\n");
    msgctl(msgid, IPC_RMID, NULL);
    exit(EXIT_SUCCESS);
}

*/
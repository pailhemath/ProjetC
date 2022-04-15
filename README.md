Compilation: 

//server:
gcc -g -pthread server.c -o server

//client:
gcc client.c -o client

//GTK
gcc test.c $(pkg-config --cflags --libs gtk+-2.0) -o test

dossier code:

test.c => contient l'outil de connexion

coucou.glade => un test de génération de l'écran avec glade qui n'a pas trop marché



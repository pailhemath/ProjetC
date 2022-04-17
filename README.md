Compilation:
//install
sudo apt-get install libgtk2.0-dev
//server:
gcc -g -pthread server.c -o server

//client:
gcc client.c -o client

//GTK
gcc server.c $(pkg-config --cflags --libs gtk+-2.0) -pthread -o server
gcc client.c $(pkg-config --cflags --libs gtk+-2.0) -o client
dossier code:

test.c => contient l'outil de connexion

coucou.glade => un test de génération de l'écran avec glade qui n'a pas trop marché



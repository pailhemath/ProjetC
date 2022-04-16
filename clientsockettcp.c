#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#define PORT 2058
int main() { // client
    int sock; struct sockaddr_in adr_s, adr_c;
    char *pseudo;
    char *message;
    char message_final[2000];

    // Créer une fonction get pseudo et getmessage.
    pseudo = "Fabien";
    message = "Bonjour";

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // Creation socket
    bzero(&adr_s,sizeof(adr_s));
    adr_s.sin_family = AF_INET;
    adr_s.sin_port = htons(PORT);
    adr_s.sin_addr.s_addr = inet_addr("127.0.0.1");
    connect(sock, (struct sockaddr *) &adr_s, sizeof(adr_s));

    // Créer le message à envoyer
    strcat(strcpy(message_final, pseudo), " : ");
    strcat(message_final, message);
    printf("%s\n", message_final);

    write(sock, message_final, 2000);
 
    close(sock);
}

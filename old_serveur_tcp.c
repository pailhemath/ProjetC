#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <netdb.h>
#include <string.h>
#include <unistd.h>	//write
#include <pthread.h> //compiler avec lpthread ou pthread

void *connection_handler(void *);
#define PORT 2058
int main() { // serveur
	int sock, nsock, lg, n, new_socket , c , *new_sock;
	char *message;
	pid_t pid;
	char buf[20];
	struct sockaddr_in adr_s, adr_c;
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // Creation socket
	bzero(&adr_s,sizeof(adr_s)); adr_s.sin_family = AF_INET; adr_s.sin_port = htons(PORT);
	adr_s.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sock, (struct sockaddr *) &adr_s, sizeof(adr_s));
	listen(sock, 5);
	printf("En attente de connexion\n\n");
	
	// Accepter les connexions des clients
	c = sizeof(struct sockaddr_in);
	while((new_socket = accept(sock, (struct sockaddr *)&adr_c, (socklen_t*)&c)))
	{
		
		
		puts("Connection acceptée");
		
		//Répond au client
		message = "Bonjour, j'ai reçu votre connexion, je vous assigne un handler\n";
		write(new_socket , message , strlen(message));
		
		pthread_t sniffer_thread;
		new_sock = malloc(1);
		*new_sock = new_socket;
		
		//Appelle le handler pour répondre au client
		if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0)
		{
			perror("Nous n'avons pas pu créer le thread");
			return 1;
		}
		
		//Attendre les threads
		pthread_join( sniffer_thread , NULL);
		puts("Handler assigné");
	}
	
	if (new_socket<0)
	{
		perror("accept failed");
		return 1;
	}
	
	/*while (1)
	{
		lg = sizeof(adr_c);
		nsock = accept(sock, (struct sockaddr *) &adr_c, &lg);
		pid = fork();
		if (pid==0)
		{
			close(sock);
			read(nsock,buf,20);
			close(nsock);
			printf("Message reçu : %s \n", buf);
			exit(0);
		}
	}*/
}


/*
 * This will handle connection for each client
 * */
void *connection_handler(void *socket_desc)
{
	//Reçois le descripteur de la socket
	int sock2 = *(int*)socket_desc;
	
	char *message;
	
	//Envoie le message au client
	message = "Greetings! I am your connection handler\n";
	write(sock2 , message , strlen(message));
	
	message = "Its my duty to communicate with you";
	write(sock2 , message , strlen(message));
	
	//Libère le pointeur
	free(socket_desc);
	
	//return 0;
}
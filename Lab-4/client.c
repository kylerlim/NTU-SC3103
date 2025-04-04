#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <sys/wait.h>

#define NUM_CLIENTS 3
#define BUFFER_SIZE 256

void error(const char *msg) {
    perror(msg);
    exit(1);
}

void create_client(const char *hostname, int port){
	int sockfd, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[BUFFER_SIZE];

//	int rand_int = (rand() % 100) + 1;
	int rand_int = (getpid() % 13 + 47);
	sprintf(buffer, "%d", rand_int);

	// Create Socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) error("ERROR opening socket");

	server = gethostbyname(hostname);
	if (server == NULL) error("ERROR no such host");

	// Setup server address struct
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
	serv_addr.sin_port = htons(port);

	// Connected
	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) error("ERROR connecting");

	printf("Client (PIDL %d) sending: %d\n", getpid(), rand_int);

	n = write(sockfd, buffer, strlen(buffer));
	if (n < 0) error("ERROR writing to socket");

	// Read response
	memset(buffer, 0, BUFFER_SIZE);
	n = read(sockfd, buffer, BUFFER_SIZE - 1);
	if (n < 0) error("ERROR reading from socket");

	printf("Client (PID: %d) received: %s\n", getpid(), buffer);

	close(sockfd);
}


int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s [hostname] [port]\n", argv[0]);
        exit(1);
    }

	const char *hostname = argv[1];
	int port = atoi(argv[2]);



	for (int i = 0; i < NUM_CLIENTS; i++){
		srand(time(NULL));
		pid_t pid = fork();
		if (pid < 0){
			error("ERROR forking");
		}
		if (pid == 0){
			usleep(3000);
			create_client(hostname, port);
			exit(0);
		}
	}

	for (int i = 0; i < NUM_CLIENTS; i++){
		wait(NULL);
	}


    printf("All processes completed...\nShutting down...");

    return 0;
}

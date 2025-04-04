#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_THREADS 3  // Maximum concurrent clients
#define BUFFER_SIZE 256

int active_threads = 0;  // Track active threads
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;  // Mutex for thread counter

void error(const char *msg) {
    perror(msg);
    exit(1);
}

// Function to handle each client in a separate thread
void *handle_client(void *arg) {
    char return_buff[256];
    int newsockfd = *(int *)arg;
    free(arg);  // Free dynamically allocated memory

    char buffer[BUFFER_SIZE];
    int n;

    memset(buffer, 0, BUFFER_SIZE);
    n = read(newsockfd, buffer, BUFFER_SIZE - 1);
    if (n < 0) error("ERROR reading from socket");

    printf("Message received: %s\n", buffer);

    usleep(2000000);
    int return_num = 5 * atoi(buffer);
    sprintf(return_buff, "%d", return_num);

    n = write(newsockfd, return_buff, 20);
    n = write(newsockfd, "Message acknowledged", 21);
    if (n < 0) error("ERROR writing to socket");

    close(newsockfd);

    // Decrement active thread count
    pthread_mutex_lock(&lock);
    active_threads--;
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main(int argc, char *argv[]) {
    int sockfd, *newsockfd, port, clilen;
    struct sockaddr_in serv_addr, cli_addr;
    pthread_t thread_id;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s [port]\n", argv[0]);
        exit(1);
    }

    port = atoi(argv[1]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR opening socket");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR binding to socket");

    listen(sockfd, 5);
    printf("Server listening on port %d...\n", port);

    while (1) {  // Infinite loop to accept multiple clients
        clilen = sizeof(cli_addr);

        // Limit the number of concurrent threads
        pthread_mutex_lock(&lock);
        if (active_threads >= MAX_THREADS) {
            pthread_mutex_unlock(&lock);
            sleep(1);  // Wait for a thread to become available
            continue;
        }
        pthread_mutex_unlock(&lock);

        newsockfd = malloc(sizeof(int));
        if (!newsockfd) error("ERROR allocating memory");
        
        *newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, (socklen_t*)&clilen);
        if (*newsockfd < 0) {
            free(newsockfd);
            error("ERROR on accept");
        }

        // Increment active thread count
        pthread_mutex_lock(&lock);
        active_threads++;
        pthread_mutex_unlock(&lock);

        // Create a new thread to handle the client
        if (pthread_create(&thread_id, NULL, handle_client, newsockfd) != 0)
            error("ERROR creating thread");

        pthread_detach(thread_id);  // Automatically clean up finished threads
    }

    close(sockfd);
    pthread_mutex_destroy(&lock);
    return 0;
}

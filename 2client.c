#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define PORT 8080
#define MAXLINE 1024
int main() {
	int sockfd;
	int result_received;
	struct sockaddr_in	 servaddr;
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
int n,len;
int temp[2];
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
    printf("Enter the 5 Sentences:\n");
    char input[5][MAXLINE];
    for (int i = 0; i < 5; i++)
        scanf(" %[^\n]s", input[i]);
	sendto(sockfd, &input, sizeof(input),
		0, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));
	printf("Message is sent.\n");
	n = recvfrom(sockfd, &temp,sizeof(temp),
				0, (struct sockaddr *) &servaddr,
				&len);
    printf("Longest sentence is `%s`\nNo of words = %d\n",input[temp[0]],temp[1]);
	close(sockfd);
	return 0;
}
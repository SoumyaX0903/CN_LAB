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

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	
	int n, len;
    char input[MAXLINE];
	printf("Enter a message:\n");
	scanf("%[^\n]s",input);
	sendto(sockfd, (const char*)input, strlen(input),
		0, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));
	printf("Message is sent.\n");
	n = recvfrom(sockfd, &result_received,sizeof(int),
				0, (struct sockaddr *) &servaddr,
				&len);
	printf("No of words received from server is : %d\n", result_received);
	close(sockfd);
	return 0;
}
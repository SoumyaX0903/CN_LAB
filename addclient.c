#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define PORT	 8080
#define MAXLINE 1024
// Driver code
int main() {
	int sockfd;
	int result_received;
	char *hello = "Hello from client";
	struct sockaddr_in	 servaddr;

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	
	int n, len;
	int a[2];printf("Enter two number:\n");
	scanf("%d",&a[0]);scanf("%d",&a[1]);
	sendto(sockfd, &a, sizeof(a),
		0, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));
	printf("Numbers are sent.\n");
	n = recvfrom(sockfd, &result_received, sizeof(int),
				0, (struct sockaddr *) &servaddr,
				&len);
	printf("Sum received from server is : %d\n", result_received);

	close(sockfd);
	return 0;
}
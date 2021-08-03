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
	char message_received[MAXLINE];
	struct sockaddr_in servaddr, cliaddr;
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	int len, n;
	len = sizeof(cliaddr); 
	n = recvfrom(sockfd, (char*)message_received,MAXLINE,
				0, ( struct sockaddr *) &cliaddr,
				&len);
	message_received[n]='\0';
    printf("%s\n",message_received);
    int c=0;
	for(int i=0;i<strlen(message_received);i++)
	{
		if(message_received[i]==' ')c++;
	}
    c=c+1;
    printf("%d\n",c);
	sendto(sockfd,&c,sizeof(int),
		0, (const struct sockaddr *) &cliaddr,
			len);
	printf("Result sent.\n");
	return 0;
}

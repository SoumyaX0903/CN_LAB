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

typedef struct structure 
{
    int ID;
    char* name;
}structure;

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
    structure data;

    printf("Enter the ID\n ");
    scanf("%d",&data.ID);
    
    
	printf("Enter the name:\n");
    scanf("\n");
    
    data.name=(char *)malloc(20*sizeof(char));
	scanf("%[^\n]s",data.name);
    
	sendto(sockfd,&data,sizeof(data),
    	0, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));
	printf("Data is sent.\n");

    
	n = recvfrom(sockfd, &data, sizeof(data),
				0, (struct sockaddr *) &servaddr,
				&len);
	printf("The structure received from the server is :\n ID: %d\n Name: %s\n", data.ID,data.name);
	close(sockfd);
	return 0;
}

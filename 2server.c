#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include<limits.h>
#define PORT 8080
#define MAXLINE 1024
int main() {
	int sockfd;
	char message_received [5][MAXLINE];
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
	n = recvfrom(sockfd, &message_received,sizeof(message_received),
				0, ( struct sockaddr *) &cliaddr,
				&len);
	
    int max=INT_MIN,pos=0;
	for(int i=0;i<5;i++)
	{
        int l=strlen(message_received[i]);
        if(l>max){max=l,pos=i;}
	}
    int ans[2];ans[0]=pos;int c=0;
    for(int i=0;i<strlen(message_received[pos]);i++)
    {
        if(message_received[pos][i]==' ')c++;
    }
    ans[1]=c+1;    
	sendto(sockfd,&ans,sizeof(ans),
		0, (const struct sockaddr *) &cliaddr,
			len);
	printf("Result sent.\n");
	return 0;
}

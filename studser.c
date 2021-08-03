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
  
    
    struct sockaddr_in servaddr, cliaddr;
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
         perror("socket creation failed");
       exit(EXIT_FAILURE);
     }
      memset(&servaddr, 0, sizeof(servaddr));
      memset(&cliaddr, 0, sizeof(cliaddr));
      servaddr.sin_family = AF_INET;// IPv4
      servaddr.sin_addr.s_addr = INADDR_ANY;
      servaddr.sin_port = htons(PORT);
     if ( bind(sockfd, (const struct sockaddr *)&servaddr,
 sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len,n;
    len = sizeof(cliaddr);
    structure data;
    
    n=recvfrom(sockfd,&data,sizeof(data),0,(struct sockaddr*)&cliaddr,&len);
    // printf("Data received!\n");
    // printf("The structure received from the client is :\n ID: %d\n Name: %s\n", data.ID,data.name);
    // printf("\nReversing the ID...\n");
    int rev=0;
    while(data.ID>0)
    {
        rev=10*rev+data.ID%10;
        data.ID/=10;
    }
    data.ID=rev;

    sendto(sockfd, &data, sizeof(data),
          0,(const struct sockaddr *) &cliaddr,
           len);
        //  printf("Data sent after modification\n");
 
  return 0;
}

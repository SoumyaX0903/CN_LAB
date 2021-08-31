#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
typedef struct structure 
{
    int a;
    int b;
    char op;
}structure;
int main(int argc, char const *argv[])
{
int server_fd, new_socket, valread;
struct sockaddr_in address;
int addrlen = sizeof(address);
char buffer[1024] = {0};
// Creating socket file descriptor
if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
{
perror("socket failed");
exit(EXIT_FAILURE);
}
address.sin_family = AF_INET;
address.sin_addr.s_addr = INADDR_ANY;
address.sin_port = htons(PORT);
// Forcefully attaching socket to the port 8080
if (bind(server_fd, (struct sockaddr *)&address,
sizeof(address)) < 0)
{
perror("bind failed");
exit(EXIT_FAILURE);
}
if (listen(server_fd, 3) < 0)
{
perror("listen");
exit(EXIT_FAILURE);
}
if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
(socklen_t *)&addrlen)) < 0)

{
perror("accept");
exit(EXIT_FAILURE);
}
structure recvdata;
float ans=0.0;
valread = read(new_socket, &recvdata, sizeof(recvdata));
switch(recvdata.op)
{
    case '+':{ans=recvdata.a+recvdata.b;break;}
    case '-':{ans=recvdata.a-recvdata.b;break;}
    case '*':{ans=recvdata.a*recvdata.b;break;}
    case '/':{ans=(float)recvdata.a/recvdata.b;break;}
    default:{ans=-99999.999;break;}
}
send(new_socket, &ans, sizeof(float), 0);
printf("Result sent\n");
close(new_socket); // closes this particular connection
close(server_fd);
return 0;
}
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>

int main()
{
int server_sockfd, client_sockfd;
int server_len, client_len;
struct sockaddr_in server_address;
struct sockaddr_in client_address;

server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

server_address.sin_family = AF_INET;
server_address.sin_addr.s_addr = htonl(INADDR_ANY);
server_address.sin_port = htons(30000);
server_len = sizeof(server_address);
bind(server_sockfd, (struct sockaddr *)&server_address,server_len);

/* Create a connection queue, ignore child exit details and wait for
clients. */

listen(server_sockfd, 5);

signal(SIGCHLD, SIG_IGN);

while(1) {
char ch;

printf("server waiting\n");

/* Accept connection. */

client_len = sizeof(client_address);
client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address, &client_len);

/* Fork to create a process for this client and perform a test to see
whether we're the parent or the child. */

if(fork() == 0) {

/* If we're the child, we can now read/write to the client on
client_sockfd.
The five second delay is just for this demonstration. */
while(ch != -1){
read(client_sockfd, &ch, 1);
sleep(5);
if(ch=='a')
  printf("Bonjour");
write(client_sockfd, &ch, 1);
}
close(client_sockfd);
}

/* Otherwise, we must be the parent and our work for this client is
finished. */

else {
close(client_sockfd);
}
}
}

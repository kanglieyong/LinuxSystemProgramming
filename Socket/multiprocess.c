#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  int server_sockfd, client_sockfd;
  int server_len, client_len;
  struct sockaddr_in server_address;
  struct sockaddr_in client_address;

  server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);
  server_address.sin_port = htons(9734);
  server_len = sizeof(server_address);
  bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

  listen(server_sockfd, 5);

  /* ignore the exit detail of the child process */
  signal(SIGCHLD, SIG_IGN);

  for(; ;) {
    char ch;

    printf("server waiting\n");

    client_len = sizeof(client_address);
    client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
    if (fork() == 0) {
      // child process
      read(client_sockfd, &ch, 1);
      sleep(5);
      ch++;
      write(client_sockfd, &ch, 1);
      close(client_sockfd);
      exit(0);
    } else {
      // parent process
      close(client_sockfd);
    }
  }

  return 0;
}

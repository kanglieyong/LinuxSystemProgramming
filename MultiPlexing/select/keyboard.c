#include <sys/times.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/select.h>

int main()
{
  int keyboard;
  int ret, i;
  char c;
  fd_set readfds;
  struct timeval timeout;
  keyboard = open("/dev/tty", O_RDONLY | O_NONBLOCK);
  assert(keyboard > 0);

  for (;;) {
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    FD_ZERO(&readfds);
    FD_SET(keyboard, &readfds);
    ret = select(keyboard+1, &readfds, NULL, NULL, &timeout);
    if (ret == -1) {
      perror("select error");
    } else if (ret){
      if (FD_ISSET(keyboard, &readfds)) {
	i = read(keyboard, &c, 1);
	if ('\n' == c)
	  continue;
	printf("hehethe input is %c\n", c);
	if ('q' == c)
	  break;
      }
    } else if (ret == 0) {
      printf("time out\n");
    }
  }

  return 0;
}

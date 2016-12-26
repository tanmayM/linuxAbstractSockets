#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <linux/in.h>
#include <linux/un.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
//#include <netinet/in.h>
#include <net/if.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>


#define SERVER_SOCKET "#hookctlDaemon"
int main(int argc, char** argv) {
    int ret;

    int sockfd, len, err=0;
    char buff[42] = { 0 };
    struct sockaddr_un sAddr, rAddr;
    socklen_t sockLen = sizeof(sAddr.sun_family) + strlen(SERVER_SOCKET);

    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);

    if (sockfd < 0) {
        printf("Failed to create the socket....");
        fflush(NULL);
        return 1;
    }

    memset(&sAddr, 0, sizeof(sAddr));
    sAddr.sun_family = AF_UNIX;
    memcpy(sAddr.sun_path, SERVER_SOCKET, sizeof(SERVER_SOCKET)-1);
    sAddr.sun_path[0] = 0;

    if (bind(sockfd, (const struct sockaddr *) &sAddr, sockLen) < 0) {
        printf("Socket Bind Failed....");
        fflush(NULL);
        return 1;
    }

   while (1) 
   {

       printf("\nwaiting to accept the connection....\n");
       fflush(NULL);

       char buf[40];

       int readret = recvfrom(sockfd, buf, 30, 0, (struct sockaddr *)&rAddr, &sockLen);

       printf("Received %d bytes on socket. Actual data=%s\n", readret, buf);
   }
    return 1;
}

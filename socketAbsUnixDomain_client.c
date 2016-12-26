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

#define CLIENT_SOCKET "#hookctlClient"
#define SERVER_SOCKET "#hookctlDaemon"

int main(int argc, char** argv) {
    int ret;

    int sockfd, len, err=0;
    char buff[42] = { 0 };
    struct sockaddr_un sAddr, clientAddr;
    socklen_t sockLen = sizeof(sAddr.sun_family) + strlen(CLIENT_SOCKET);

    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);

    if (sockfd < 0) {
        printf("Failed to create the socket....");
        fflush(NULL);
        return 1;
    }

    memset(&clientAddr, 0, sizeof(clientAddr));
    clientAddr.sun_family = AF_UNIX;
    memcpy(clientAddr.sun_path, CLIENT_SOCKET, sizeof(CLIENT_SOCKET)-1);
    clientAddr.sun_path[0] = 0;

    if (bind(sockfd, (const struct sockaddr *) &clientAddr, sockLen) < 0) {
        printf("Socket Bind Failed....");
        fflush(NULL);
        return 1;
    }

    memset(&sAddr, 0, sizeof(sAddr));
    sAddr.sun_family = AF_UNIX;
    memcpy(sAddr.sun_path, SERVER_SOCKET, sizeof(SERVER_SOCKET)-1);
    sAddr.sun_path[0] = 0;

    {

        printf("\nSending data now....\n");
        fflush(NULL);

        char buf[40];
        buf[0] = '-';
        buf[1] = 'A';
        buf[2] = '\0';

        int bytesSent = sendto(sockfd, buf, 30, 0, (struct sockaddr *)&sAddr, sockLen);
        printf("\nsent %d bytes\n", bytesSent);
        if(-1==bytesSent)
        {
            printf("Error=%s (%d)\n", strerror(errno), errno);
        }

    }

    close(sockfd);
    return 1;
}

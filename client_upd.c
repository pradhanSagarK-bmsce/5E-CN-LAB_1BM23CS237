#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in servaddr;
    socklen_t servlen;
    char buffer[256], c[20000];

    if (argc < 3)
    {
        printf("Usage: %s <server_ip> <port>\nExample: %s 127.0.0.1 7777\n", argv[0], argv[0]);
        exit(1);
    }

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("socket creation failed");
        exit(1);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(portno);
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);

    printf("Enter the file name with complete path: ");
    scanf("%s", buffer);

    servlen = sizeof(servaddr);
    n = sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&servaddr, servlen);
    if (n < 0)
    {
        perror("sendto error");
        close(sockfd);
        exit(1);
    }

    bzero(c, sizeof(c));
    printf("Receiving file contents...\n");

    n = recvfrom(sockfd, c, sizeof(c) - 1, 0, (struct sockaddr *)&servaddr, &servlen);
    if (n < 0)
    {
        perror("recvfrom error");
        close(sockfd);
        exit(1);
    }

    c[n] = '\0';
    printf("File content received:\n--------------------------------\n");
    fputs(c, stdout);
    printf("\n--------------------------------\n");

    close(sockfd);
    return 0;
}

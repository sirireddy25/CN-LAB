#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define PORTNO 10200

int main() {
    int len, result, sockfd, n = 1, i;
    struct sockaddr_in address;
    char ch[256], buf[256];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORTNO);
    len = sizeof(address);
    result = connect(sockfd, (struct sockaddr *)&address, len);
    if (result == -1) {
        perror("\nCLIENT ERROR");
        exit(1);
    }
    printf("Enter anything: ");
    fgets(ch, sizeof(ch), stdin);

    for(i = 0; i < strlen(ch); i++) 
            ch[i] = ch[i] + 4;

    write(sockfd, ch, strlen(ch));
    printf("Message back from the server: ");
    while (n) {
        n = read(sockfd, buf, sizeof(buf));
        puts(buf);
    }
}
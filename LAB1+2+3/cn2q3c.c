/*
Write a concurrent TCP daytime server ‘C’ program. Along with the result, server
should also send the process id to the client.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<time.h>
#define PORTNO 10200

int main(){
	int sockfd;
	struct sockaddr_in address;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET;
	address.sin_port = htons(PORTNO);
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	int result = connect(sockfd, (struct sockaddr*)&address, sizeof(address));
	if(result == -1){
		perror("CLIENT ERROR");
		exit(0);
	}

	char str[100];
	time_t buf[100];
	int n, pid;
	printf("Enter a string: \n");
	fgets(str, sizeof(str), stdin);

	write(sockfd, str, sizeof(str));
	n = read(sockfd, &buf, sizeof(&buf));
	printf("current date and time: %s\n", ctime(&buf));
	n = read(sockfd, &pid, sizeof(&pid));
	printf("pid: %d\n", pid);

}
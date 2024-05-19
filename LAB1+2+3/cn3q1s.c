/*
Write a UDP client-server program where the client sends rows of a matrix, and the
servercombines them together as a matrix.
*/

//in server, seraddr used for binding
//cliaddr used for sendto and recvfrom

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h> 
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#define PORTNO 10200

int main(){
	int sockfd;
	struct sockaddr_in seraddr, cliaddr;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(PORTNO);
	seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	bind(sockfd, (struct sockaddr*)&seraddr, sizeof(seraddr));

	int len = sizeof(cliaddr);
	int c, r;
	int m = recvfrom(sockfd, &r, sizeof(r), 0, (struct sockaddr*)&cliaddr, &len);
	m = recvfrom(sockfd, &c, sizeof(c), 0, (struct sockaddr*)&cliaddr, &len);
	int mat[r][c];
	int rows[c];

	for(int i = 0; i < r; i++){
		int m = recvfrom(sockfd, rows, sizeof(rows), 0, (struct sockaddr*)&cliaddr, &len);
		for(int j = 0; j < c; j++)
			mat[i][j] = rows[j];
	}

	printf("matrix: \n");
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++)
			printf("%d ", mat[i][j]);
		printf("\n");
	}


}
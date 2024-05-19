/*
Write a UDP client-server program where the client sends rows of a matrix, and the
servercombines them together as a matrix.
*/

/*see sendto and recvfrom syntax !!!*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h> /*extra header for udp*/
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#define PORTNO 10200

int main(){
	int sockfd;
	struct sockaddr_in address;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	address.sin_family = AF_INET;
	address.sin_port = htons(PORTNO);
	address.sin_addr.s_addr = inet_addr("127.0.0.1");

	int r, c;
	int len = sizeof(address);
	printf("Enter no. of rows: \n");
	scanf("%d", &r);
	int n = sendto(sockfd, &r, sizeof(r), 0, (struct sockaddr*)&address, len); //WHILE SENDING INT NO NEED TO PUT & IN SIZEOF !!!

	printf("Enter no. of columns: \n");
	scanf("%d", &c);
	n = sendto(sockfd, &c, sizeof(c), 0, (struct sockaddr*)&address, len);

	int rows[c];

	printf("Enter elements: \n");
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			scanf("%d", &rows[j]);
		}
		n = sendto(sockfd, rows, sizeof(rows), 0, (struct sockaddr*)&address, len);
	}

}
/*
Implement concurrent Remote Math Server To perform arithmetic operations in the
server and display the result to the client. The client accepts two integers and an
operator from the user and sends it to the server. The server then receives integers and
operator. The server will perform the operation on integers and sends the result back 
to the client which is displayed on the client screen. Then both the processes
terminate.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#define PORTNO 10200

int main(){
	int sockfd, newsockfd;
	struct sockaddr_in seraddr, cliaddr;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(PORTNO);
	seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	bind(sockfd, (struct sockaddr*)&seraddr, sizeof(seraddr));
	listen(sockfd, 5);
	while(1){
		int clilen = sizeof(clilen);
		newsockfd = accept(sockfd, (struct sockaddr*)&cliaddr, &clilen);
		if(fork() == 0){
			float arr[3];
			float ans;
			int n = read(newsockfd, arr, sizeof(arr));
			if(arr[0] == 1)
				ans = arr[1] + arr[2];
			else if(arr[0] == 2)
				ans = arr[1] - arr[2];
			else if(arr[0] == 3)
				ans = arr[1] * arr[2];
			else if(arr[0] == 4)
				ans = arr[1] / arr[2];

			write(newsockfd, &ans, sizeof(&ans));
			close(newsockfd);
			exit(0);
		}
		else
			close(newsockfd);
	}
}
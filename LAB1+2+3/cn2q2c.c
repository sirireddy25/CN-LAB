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
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
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
	float arr[3];
	float ans;
	printf("Enter operation choice: \n");
	printf("1. +\n2. -\n3. *\n4. /\n");
	scanf("%f", &arr[0]);

	printf("Enter operand1: \n");
	scanf("%f", &arr[1]);

	printf("Enter operand2: \n");
	scanf("%f", &arr[2]);
	write(sockfd, arr, sizeof(arr));

	int n = read(sockfd, &ans, sizeof(&ans));
	printf("Result: %.2f\n", ans);
}
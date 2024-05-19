//Write a TCP concurrent client server program where server accepts integer array from

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#define PORTNO 10203

int main(){
	struct sockaddr_in address;
	int sockfd;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(PORTNO);

	int result = connect(sockfd, (struct sockaddr*)&address, sizeof(address));
	if(result == -1){
		perror("CLIENT ERROR");
		exit(0);
	}

	int arr[10];
	int pid;
	int sorted[10];
	printf("enter array elements: \n");
	for(int i = 0; i < 10; i++)
		scanf("%d", &arr[i]);

	write(sockfd, arr, sizeof(arr));

	printf("sorted array: \n");
	read(sockfd, sorted, sizeof(sorted));
	for(int i = 0; i < 10; i++)
		printf("%d  ", sorted[i]);
	read(sockfd, &pid, sizeof(&pid));
	printf("\npid: %d\n", pid);
}

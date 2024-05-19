//Write a TCP concurrent client server program where server accepts integer array from
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/wait.h>
#define PORTNO 10203

int main(){
	int sockfd, newsockfd;
	struct sockaddr_in address, cliaddress;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(PORTNO);
	bind(sockfd, (struct sockaddr*)&address, sizeof(address));
	listen(sockfd, 5);
	while(1){
		int clilen = sizeof(clilen);
		newsockfd = accept(sockfd, (struct sockaddr*)&cliaddress, &clilen);
		if(fork() == 0){
			int arr[10];
			int n, pid;
			pid = getpid();
			n = read(newsockfd, arr, sizeof(arr));
			for(int i = 0 ; i < 10; i++){
				for(int j = i+1; j < 10; j++){
					if(arr[i] > arr[j]){
						int temp = arr[i];
						arr[i] = arr[j];
						arr[j] = temp;
					}
				}
			}
			write(newsockfd, arr, sizeof(arr));
			write(newsockfd, &pid, sizeof(pid)); 
			close(newsockfd);
			exit(0);
		}
		else
			close(newsockfd);
	}
}

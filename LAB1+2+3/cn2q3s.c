

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
	int sockfd, newsockfd;
	struct sockaddr_in seraddr, cliaddr;
	sockfd = socket(AF_INET, SOCK_STREAM,0);
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(PORTNO);
	seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	bind(sockfd, (struct sockaddr*)&seraddr, sizeof(seraddr));
	listen(sockfd, 5);

	while(1){
		int clilen = sizeof(clilen);
		newsockfd = accept(sockfd, (struct sockaddr*)&cliaddr, &clilen);
		if(fork() == 0){
			int pid, n;
			char buf[100];
			time_t t;
			n = read(newsockfd, buf, sizeof(buf));
			time(&t);
			write(newsockfd, &t, sizeof(&t));
			pid = getpid();
			write(newsockfd, &pid, sizeof(&pid));
			close(newsockfd);
			exit(0);
		}
		else
			close(newsockfd);
	}
}


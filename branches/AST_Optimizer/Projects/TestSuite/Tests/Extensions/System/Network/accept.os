#!/usr/local/bin/oscript

public void Main(int argc = 0, string args = "") {
	print("AF_INET = " + AF_INET);
	print("SOCK_STREAM = " + SOCK_STREAM);

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	print("sockfd = " + sockfd);

	int result = bind(sockfd, "127.0.0.1:33333");
	print("result = " + result);

	result = listen(sockfd, 50);
	print("result = " + result);

	result = accept(sockfd, "127.0.0.1:33333");
	print("result = " + result);

	//close(sockfd);
}


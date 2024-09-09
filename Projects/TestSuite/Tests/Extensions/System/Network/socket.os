#!/usr/local/bin/slang

public void Main(int argc = 0, string args = "") {
	print("AF_INET = " + AF_INET);
	print("SOCK_STREAM = " + SOCK_STREAM);

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	print("sockfd = " + sockfd);

	//close(sockfd);
}


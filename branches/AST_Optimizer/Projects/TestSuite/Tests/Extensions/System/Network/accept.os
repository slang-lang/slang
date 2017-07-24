#!/usr/local/bin/oscript

import System.Network.Socket;

public void Main(int argc = 0, string args = "") {
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	print("sockfd = " + sockfd);

	ISocketAddress sockaddr = ISocketAddress new IPv4Address("127.0.0.1", 33333);

	int result = bind(sockfd, sockaddr);
	print("result = " + result);

	result = listen(sockfd, 50);
	print("result = " + result);

	result = accept(sockfd);
	print("result = " + result);
}


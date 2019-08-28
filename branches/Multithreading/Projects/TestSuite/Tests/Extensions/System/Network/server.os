#!/usr/local/bin/oscript

import System.Network.Socket;

public void Main(int argc = 0, string args = "") {
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	print("sockfd = " + sockfd);

	if ( sockfd == -1 ) {
		print("cannot create socket");
		return;
	}

	ISocketAddress sockaddr = ISocketAddress new IPv4Address(INADDR_ANY, 33333);

	int result = bind(sockfd, sockaddr);
	print("bind = " + result);

	if ( result == -1 ) {
		print("bind failed");
		close(sockfd);
		return;
	}

	result = listen(sockfd, 10);
	print("listen = " + result);

	if ( result == -1 ) {
		print("listen failed");
		close(sockfd);
		return;
	}

	int connectfd = accept(sockfd);
	print("connectfd = " + connectfd);

	if ( connectfd < 0 ) {
		print("accept failed");
		close(sockfd);
		return;
	}

/*
	// get length of following string
	int length = readi(connectfd);
	print("length = " + length);
*/
	int length = -1;

	// get string data
	string value = reads(connectfd, length);
	print("read = " + value);

	result = close(connectfd);
	print("close = " + result);

	result = close(sockfd);
	print("close = " + result);
}


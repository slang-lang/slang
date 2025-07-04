#!/usr/bin/env slang

import System.Network.Socket;

public void Main(int argc = 0, string args = "") {
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	print("sockfd = " + sockfd);

	if ( sockfd == -1 ) {
		print("cannot create socket");
		return;
	}

	int result = bind(sockfd, ISocketAddress new IPv4Address("127.0.0.1", 33333));
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
	print("accept = " + connectfd);

	if ( connectfd < 0 ) {
		print("accept failed");
		close(sockfd);
		return;
	}

	// get string data
	string value = reads(connectfd, -1);
	print("read = " + value);

	result = close(connectfd);
	print("close = " + result);

	result = close(sockfd);
	print("close = " + result);
}


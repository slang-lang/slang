#!/usr/local/bin/oscript

import System.Network.Socket;

public void Main(int argc = 0, string args = "") {
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if ( sockfd == -1 ) {
		print("cannot create socket");
		return;
	}

	ISocketAddress sockaddr = ISocketAddress new IPv4Address("127.0.0.1", 33333);

	int result = bind(sockfd, sockaddr);
	if ( result == -1 ) {
		print("bind failed");
		close(sockfd);
		return;
	}

	result = listen(sockfd, 10);
	if ( result == -1 ) {
		print("listen failed");
		close(sockfd);
		return;
	}

	int connectfd = accept(sockfd);
	if ( connectfd < 0 ) {
		print("accept failed");
		close(sockfd);
		return;
	}

	string cmd_data;
	int cmd_length;

	bool running = true;
	while ( running ) {
		// get length of following string
		cmd_length = readi(connectfd);

		if ( !cmd_length ) {
			continue;
		}

		// get payload data
		cmd_data = reads(connectfd, cmd_length);

		if ( cmd_data == "quit" ) {
			running = false;
		}

		print("received: \"" + cmd_data + "\"");
	}

	result = close(connectfd);
	print("close = " + result);

	result = close(sockfd);
	print("close = " + result);
}


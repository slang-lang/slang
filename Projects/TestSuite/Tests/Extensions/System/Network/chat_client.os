#!/usr/local/bin/slang

import System.Network.Socket;

public void Main(int argc = 0, string args = "") {
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if ( sockfd == -1 ) {
		print("cannot create socket");
		return;
	}

	ISocketAddress sockaddr = ISocketAddress new IPv4Address("127.0.0.1", 33333);

	int result = connect(sockfd, sockaddr);
	if ( result == -1 ) {
		print("connect failed");
		return;
	}

	string cmd_data;
	int cmd_length;

	bool running = true;
	while ( running ) {
		write("> ");
		cmd_data = string cin();
		cmd_length = strlen(cmd_data);

		result = writei(sockfd, cmd_length);
		if ( result == -1 ) {
			print("writing of command length failed");
			return;
		}

		result = writes(sockfd, cmd_data);
		if ( result == -1 ) {
			print("writing of command payload failed");
			return;
		}

		if ( cmd_data == "quit" ) {
			running = false;
		}
	}

	result = close(sockfd);
	print("close = " + result);
}


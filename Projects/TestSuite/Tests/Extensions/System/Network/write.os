#!/usr/local/bin/slang

import System.Network.Socket;

public void Main(int argc = 0, string args = "") {
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	print("sockfd = " + sockfd);

	if ( sockfd == -1 ) {
		print("cannot create socket");
		return;
	}

	ISocketAddress sockaddr = ISocketAddress new IPv4Address("127.0.0.1", 33333);

	int result = connect(sockfd, sockaddr);
	print("connect = " + result);

	result = writes(sockfd, "hallo");
	print("write = " + result);

	result = close(sockfd);
	print("close = " + result);
}


#!/usr/local/bin/slang

import System.Network.Socket;

public void Main(int argc = 0, string args = "") {
	print("AF_INET = " + AF_INET);
	print("SOCK_STREAM = " + SOCK_STREAM);

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	print("sockfd = " + sockfd);

	ISocketAddress sockaddr = ISocketAddress new IPv4Address("127.0.0.1", 33333);

	print("result = " + connect(sockfd, sockaddr));
	print("clost = " + close(sockfd));
}


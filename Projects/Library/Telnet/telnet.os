#!/usr/local/bin/oscript

// Library import
import libParam.ParameterHandler;
import System.Network.Socket;


public void Main(int argc = 0, string args = "") {
	var params = new ParameterHandler(argc, args, true);
	if ( params.empty() ) {
		print("Usage: program <host> <port>");
		exit(-1);
	}

	int numParams = params.size();
	if ( numParams < 2 ) {
		print("invalid number of arguments!");
		exit(-1);
	}

	string address = params.at(numParams - 2).Key;
	int port = int params.at(numParams - 1).Key;

	//print("address:port = " + address + ":" + port);


	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if ( sockfd == -1 ) {
		print("cannot create socket");
		return;
	}

	ISocketAddress sockaddr = ISocketAddress new IPv4Address(address, port);

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

		if ( cmd_data == "quit" ) {
			break;
		}

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
	}

	result = close(sockfd);
}


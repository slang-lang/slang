#!/usr/local/bin/oscript

// Library import
import libParam.ParameterHandler;
import System.Network.Socket;


public void Main(int argc = 0, string args = "") {
	try {
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

		print("Connected to " + address + ":" + port + "...");

		bool running = true;
		while ( running ) {
			write("> ");

			string request = string cin();
			if ( request == "quit" ) {
				break;
			}

			result = writes(sockfd, request + LINEBREAK + LINEBREAK);
			if ( result == -1 ) {
				print("writing to socket failed!");
				return;
			}


			string c;
			string response;

			while ( c != LINEBREAK && (c = reads(sockfd, 1) != LINEBREAK) ) {
				response += c;
			}

			print("Response: \"" + response + "\"");
		}

		result = close(sockfd);
	}
	catch ( string e ) {
		print("Exception: " + e);
	}
	catch ( IException e ) {
		print("Exception: " + e.what());
	}
	catch {
		print("Exception: unknown exception");
	}
}

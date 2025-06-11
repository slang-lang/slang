#!/usr/bin/env slang

// Library import
import libParam;
import System.Network.Socket;


public void Main(int argc = 0, string args = "") modify {
	try {
		var params = new ParameterHandler( argc, args );
		if ( params.empty() ) {
			print( "Usage: program <host> <port>" );
			exit( -1 );
		}

		var numParams = params.size();
		if ( numParams < 2 ) {
			print( "invalid number of arguments!" );
			exit( -1 );
		}

		var address = params[ numParams - 2 ].Key;
		var port    = cast<int>( params[ numParams - 1 ].Key );

		var sockfd = socket( AF_INET, SOCK_STREAM, 0 );
		if ( sockfd == -1 ) {
			print( "cannot create socket" );
			return;
		}

		var sockaddr = ISocketAddress new IPv4Address( address, port );

		var result = connect( sockfd, sockaddr );
		if ( result == -1 ) {
			print( "connect failed" );
			return;
		}

		print( "Connected to " + address + ":" + port + "..." );

		bool running = true;
		while ( running ) {
			write( "> " );

			var request = cin();
			if ( request == "quit" ) {
				break;
			}

			result = writes( sockfd, request + LINEBREAK + LINEBREAK );
			if ( result == -1 ) {
				print( "writing to socket failed!" );
				return;
			}

			string c;
			string response;

			while ( c != LINEBREAK && ( c = reads( sockfd, 1 ) != LINEBREAK ) ) {
				response += c;
			}

			print( "Response: \"" + response + "\"" );
		}

		result = shutdown( sockfd, SHUT_RDWR );
		result = close( sockfd );
	}
	catch ( string e ) {
		print( "Error: " + e );
	}
	catch ( IException e ) {
		print( "Error: " + e.what() );
	}
	catch {
		print( "Error: unknown exception" );
	}
}


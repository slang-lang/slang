#!/usr/local/bin/oscript

import System.Network.ClientSocket;

public void Main(int argc, string args) {
	var socket = new ClientSocket("127.0.0.1", 33333);

	if ( !socket.Connect() ) {
		print("connection failed!");
		assert( false );
	}

	while ( true ) {
		socket.WriteString(cin());
	}
}


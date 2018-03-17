#!/usr/local/bin/oscript

import System.Network.ServerSocket;

public void Main(int argc = 0, string args = "") {
	var socket = new ServerSocket(33333);
	assert( socket );

	bool result;

	result = socket.Bind();
	print("bind = " + result);

	if ( result == -1 ) {
		print("bind failed");
		assert(false);
	}

	result = socket.Listen();
	print("listen = " + result);

	if ( result == -1 ) {
		print("listen failed");
		assert(false);
	}

	result = socket.Accept();
	print("accept = " + result);

	if ( !result ) {
		print("accept failed");
		assert(false);
	}

	try {
		int length = -1;

		while ( true ) {
			length = socket.ReadInt();

			if ( length > 0 ) {
				string data = socket.ReadString(length);
				print("received: " + data);

				continue;
			}
		}
	}
	catch ( IException e ) {
		print("e.what() = " + e.what());
		assert(false);
	}

	socket.Close();
}


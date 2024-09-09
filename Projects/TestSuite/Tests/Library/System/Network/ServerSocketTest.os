#!/usr/local/bin/slang

import System.Network.ServerSocket;

public void Main(int argc = 0, string args = "") {
	var socket = new ServerSocket(33333);
	assert( socket );

	bool result;

	result = socket.Bind();
	if ( !result ) {
		print("bind failed");
		assert(false);
	}

	result = socket.Listen();
	if ( !result ) {
		print("listen failed");
		assert(false);
	}

	result = socket.Accept();
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

				if ( data == "quit" ) {
					break;
				}
			}
		}
	}
	catch ( IException e ) {
		print("e.what() = " + e.what());
		assert(false);
	}

	socket.Close();
}


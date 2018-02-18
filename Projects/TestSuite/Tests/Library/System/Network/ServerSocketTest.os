#!/usr/local/bin/oscript

import System.Network.ServerSocket;

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
}

private bool TestCase1() {
	var socket = new ServerSocket(33333);
	assert( socket );

	int result;

	result = socket.Bind();
	print("bind = " + result);

	if ( result == -1 ) {
		print("bind failed");
		return false;
	}

	result = socket.Listen();
	print("listen = " + result);

	if ( result == -1 ) {
		print("listen failed");
		return false;
	}

	int connectfd = socket.Accept();
	print("accept = " + connectfd);

	if ( connectfd < 0 ) {
		print("accept failed");
		return false;
	}


	try {

/*
	int length = -1;
	string value = socket.ReadString(length);
	print("value = " + value);
*/

	while ( true ) {
		int length = socket.ReadInt();

		if ( length > 0 ) {
			string data = socket.ReadString(length);
			print("received: " + data);

			continue;
		}
	}
	}
	catch ( IException e ) {
		print("e.what() = " + e.what());
	}

	result = socket.Close();
	print("close = " + result);

	return true;
}


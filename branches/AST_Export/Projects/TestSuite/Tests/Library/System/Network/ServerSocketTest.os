#!/usr/local/bin/oscript

import System.Network.ServerSocket;

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
}

private bool TestCase1() {
	ServerSocket socket = new ServerSocket(33333);
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

	int length = -1;
	string value = socket.ReadString(connectfd, length);
	print("value = " + value);

/*
	result = socket.Close(connectfd);
	print("close = " + result);
*/

	result = socket.Close();
	print("close = " + result);

	return true;
}


#!/usr/local/bin/oscript

import System.Network.ServerSocket;

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
}

private bool TestCase1() {
	ServerSocket socket = new ServerSocket(33333);
	assert( socket );

	int result;

	result = socket.bind();
	if ( result == -1 ) {
		print("bind failed");
		return false;
	}

	result = socket.listen();
	if ( result == -1 ) {
		print("listen failed");
		return false;
	}

	int connectfd = socket.accept();
	if ( connectfd < 0 ) {
		print("accept failed");
		return false;
	}

	int length = -1;
	string value = socket.readString(length);
	print("value = " + value);

	result = close(connectfd);
	print("close = " + result);

	result = socket.close();
	print("close = " + result);

	return true;
}


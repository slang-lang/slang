#!/usr/local/bin/oscript

import System.Network.ServerSocket;

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
}

private bool TestCase1() {
	ServerSocket socket = new ServerSocket(33333);
	assert( socket );

	return true;
}


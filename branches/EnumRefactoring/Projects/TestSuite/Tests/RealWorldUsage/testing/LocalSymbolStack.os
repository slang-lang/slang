#!/usr/local/bin/oscript

/*
 * This script is used to test the access to local variables by using an index based stack instead of resolving their names
 */

public void Main(int argc, string args) {
	int v1 = 1;
	int v2 = 2;

	print("v1 = " + v1);
	print("v2 = " + v2);
}


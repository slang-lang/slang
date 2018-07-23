#!/usr/local/bin/oscript

import System.Integer;

public void Main(int argc, string args) {
	Integer i = new Integer(173);
	print("i = " + string i);

	assert( i == 173 );

	CallMethod(i);

	assert( i == 174 );

	print("i = " + string i);
}

private void CallMethod(Integer i ref) const {
	print("CallMethod(" + (string i) + ")");

	i += 1;
}


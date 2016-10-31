#!/usr/local/bin/oscript

import System.Collections.List;

public void Main(int argc = 0, string argv = "") {
	assert( TestCase1() );		// not supported by now
}

private bool TestCase1() const {
	List<int> values = new List<int>();

	print("values.size() = " + values.size());

	values.push_back(5);
	values.push_back(17);

	print("values.size() = " + values.size());

	return true;
}


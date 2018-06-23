#!/usr/local/bin/oscript

import System.String;

public void Main(int argc, string args) {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
	assert( TestCase5() );
}

private bool TestCase1() const {
	print("TestCase 1: substr(0, 4)");

	string str = "This is a string";
	string substr1 = substr(str, 0, 4);
	print("substr1 = \"" + substr1 + "\"");

	return substr1 == "This";
}

private bool TestCase2() const {
	print("TestCase 2: substr(5)");

	string str = "This is a string";
	string substr1 = substr(str, 5);
	print("substr1 = \"" + substr1 + "\"");

	return substr1 == "is a string";
}

private bool TestCase3() const {
	print("TestCase 3: String.SubString(0, 4)");

	String str = new String("This is a string");
	print("str.SubString = \"" + str.SubString(0, 4) + "\"");
	
	return str.SubString(0, 4) == "This";
}

private bool TestCase4() const {
	print("TestCase 4: String.SubString(5)");

	String str = new String("This is a string");
	print("str.SubString = \"" + str.SubString(5) + "\"");

	return str.SubString(5) == "is a string";
}

private bool TestCase5() const {
	print("TestCase 5: String.At(idx)");

	String str = new String("This is a string");
	print("str.CharAt(3) = \"" + str.CharAt(3) + "\"");

	return str.CharAt(3) == "s";
}


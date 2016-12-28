#!/usr/local/bin/oscript

import System.String;
import System.StringIterator;

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
	assert( TestCase5() );
	assert( TestCase6() );
	assert( TestCase7() );
	assert( TestCase8() );
	assert( TestCase9() );
	assert( TestCase10() );
	assert( TestCase11() );
}

private bool TestCase1() const {
	print("TestCase 1: String.StartsWith");

	String str = new String("This is a string");
	print(str.ToString());
	print("str.StartsWith(\"This\") = " + str.StartsWith("This"));

	return str.StartsWith("This");
}

private bool TestCase2() const {
	print("TestCase 2: String.EndsWith");

	String str = new String("This is a string");
	print("str.EndsWith(\"ring\") = " + str.EndsWith("ring"));

	return str.EndsWith("ring");
}

private bool TestCase3() const {
	print("TestCase 3: String.ToLowerCase");

	String str = new String("This is a string");
	print("str.ToLowerCase() = " + (str.ToLowerCase() == "this is a string"));

	return str.ToLowerCase() == "this is a string";
}

private bool TestCase4() const {
	print("TestCase 4: String.ToUpperCase");

	String str = new String("This is a string");
	print("str.ToUpperCase() = " + (str.ToUpperCase() == "THIS IS A STRING"));

	return str.ToUpperCase() == "THIS IS A STRING";
}

private bool TestCase5() const {
	print("TestCase 5: String.Replace");

	String str = new String("This is a string");
	str.Replace("is", "was");

	print(string str);

	return str == "Thwas is a string";
}

private bool TestCase6() const {
	print("TestCase 6: String.ReplaceAll");

	String str = new String("This is a string");
	str.ReplaceAll("is", "was");

	print(string str);

	return str == "Thwas was a string";
}

private bool TestCase7() const {
	print("TestCase 7: String.ReplaceAll(\"SELECT * FROM parking_tickets WHERE valid_thru >= :valid_thru\", \"2016-05-31\")");

	String str = new String("SELECT * FROM parking_tickets WHERE valid_thru >= :valid_thru");
	assert(str.EndsWith(":valid_thru"));

	bool result = str.ReplaceAll(":valid_thru", "2016-05-31");
	print(string str);

	return result;
}

private bool TestCase8() const {
	print("TestCase 8: String.Find");

	String str = new String("This is a string");

	int find = str.Find("is");
	print("str.Find(\"is\") = " + find);

	find = str.Find("is", find + 1);
	print("str.Find(\"is\") = " + find);

	return find != -1;
}

private bool TestCase9() const {
	print("TestCase 9: String.Contains");

	String str = new String("This is a string");

	bool contains = str.Contains("is a");
	print("str.Contains(\"is a\") = " + contains);

	return contains;
}

private bool TestCase10() const {
	print("TestCase 10: String.getIterator");

	String str = new String("This is a string");

	System.StringIterator it = str.getIterator();
	assert( it );

	while ( it.hasNext() ) {
		string next = it.next();

		print("it.next() = " + next);
	}

	return true;
}

private bool TestCase11() const {
	print("TestCase 11: foreach");

	String str = new String("This is a string");

	int count = 0;
	foreach ( string s : str ) {
		print("str(" + count + ") = " + s);

		count++;
	}

	return true;
}


#!/usr/local/bin/oscript

import System.String;

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
	assert( TestCase12() );
	assert( TestCase13() );
	assert( TestCase14() );
	assert( TestCase15() );
	assert( TestCase16() );
}

private bool TestCase1() const {
	print("TestCase 1: String.StartsWith");

	String str = new String("This is a string");
	print("str = " + string str);
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
	print("TestCase 8: String.IndexOf");

	String str = new String("This is a string");

	int index = str.IndexOf("is");
	print("str.IndexOf(\"is\") = " + index);

	index = str.IndexOf("is", index + 1);
	print("str.IndexOf(\"is\") = " + index);

	return index != -1;
}

private bool TestCase9() const {
	print("TestCase 9: String.Contains");

	String str = new String("This is a string");

	bool contains = str.Contains("is a");
	print("str.Contains(\"is a\") = " + contains);

	return contains;
}

private bool TestCase10() const {
	print("TestCase 10: String.Split");

	String str = new String("This is a string");

	StringIterator it = str.Split();
	assert( it );

	while ( it.hasNext() ) {
		it.next();

		print("it.current() = '" + it.current() + "'");
	}

	return true;
}

private bool TestCase11() const {
	print("TestCase 11: foreach");

	String str = new String("This is a string");

	int count = 0;
	foreach ( string s : str.Split() ) {
		print("str(" + count + ") = '" + s + "'");

		count++;
	}
	assert( count == 4 );

	count = 0;
	write("'");
	foreach ( string c : str ) {
		//print("str[" + count + "] = '" + c + "'");
		write(c);

		count++;
	}
	writeln("'");

	return true;
}

private bool TestCase12() const {
	print("TestCase 12: subscript operator");

	String str = new String("This is a string");
	print("str[6] = " + str[6]);

	return str[6] == "s";
}

private bool TestCase13() const {
	print("TestCase 13: CharAt");

	String str = new String("This is a string");
	print("str.CharAt(6) = " + str.CharAt(6));

	return str.CharAt(6) == "s";
}

private bool TestCase14() const {
	print("TestCase 14: LastIndexOf");

	String str = new String("This is a string");

	return str.LastIndexOf("is") == 5;
}

private bool TestCase15() const {
	print("TestCase 15: Length && RemoveCharAt");

	String str = new String("This is a string");

	assert( str.Length() == 16 );

	str.RemoveCharAt(5);

	assert( str.Length() == 15 );

	str.RemoveCharAt(12);

	assert( str.Length() == 14 );

	return true;
}

private bool TestCase16() const {
	print("TestCase 10: String.SplitBy");

	String str = new String("This is a string");

	StringIterator it = str.SplitBy("i");
	assert( it );

	while ( it.hasNext() ) {
		it.next();

		print("it.current() = '" + it.current() + "'");

	}

	return true;
}



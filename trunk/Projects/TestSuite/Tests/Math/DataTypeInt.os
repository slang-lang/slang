#!/usr/local/bin/oscript

public void Main(int argc = 0, string argv = "") {
	int value = 1731389;

	print("value = " + value);

	assert( (string value) == "1731389" );

/* integer values with 'i' postfix have been removed because they would allow ackward constructs like 173i.1389f
	int value2 = 1731389i;

	print("value2 = " + value2);

	assert( (string value2) == "1731389" );
*/
}


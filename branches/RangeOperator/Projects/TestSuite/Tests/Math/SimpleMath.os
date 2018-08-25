#!/usr/local/bin/oscript

public void Main(int argc = 1, string argv = "") {
	int myInt = 100;
	print("myInt = " + myInt);

	myInt = myInt / 10; //myInt is now 10
	print("myInt = " + myInt);

	myInt = myInt * 10; //myInt is back to 100
	print("myInt = " + myInt);

	myInt = myInt + 50; //myInt is up to 150
	print("myInt = " + myInt);

	myInt = myInt - 50; //myInt is back to where it started
	print("myInt = " + myInt);

	myInt = myInt + 100 * 2; // myInt is now 300 because multiplication takes precedence over addition
	print("myInt = " + myInt);

	myInt = (myInt + 100) * 2; // myInt is now 800 because we have changed the precedence using parentheses
	print("myInt = " + myInt);
}


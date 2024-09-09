#!/usr/local/bin/slang

import System.Boolean;
import System.Integer;

public void Main(int argc, string args) {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
}

private void Reference(int value ref) {
	value += 2;
}

private void Reference(Integer value ref) {
	value += 2;
}

private bool TestCase1() const {
	print("TestCase 1: Reference");

	int value = 173;

	print("value = " + value);
	Reference(value);
	print("value = " + value);

	Integer intVal = new Integer(173);
	print("intVal = " + string intVal);
	Reference(intVal);
	print("intVal = " + string intVal);

	return value == 173 && intVal == 175;
}

private bool TestCase2() const {
	print("TestCase 2: Integer");

	Integer value = new Integer(173);
	value = 17;

	value = value * 2;
	print("value = " + string value);

	value = value - 2;
	print("value = " + string value);

	value = value / 2;
	print("value = " + string value);

	return value == 16;
}

private bool TestCase3() const {
	print("TestCase 3: Boolean");

	Boolean value = new Boolean(true);
	value = !false;

	print("value = " + string value);
	print("!value = " + !value);
	//value = Boolean !value;
	//print("value = " + value.ToString());

	return true;
}


#!/usr/local/bin/oscript

public void Main(int argc = 0, string argv = "") {
	print("argc = " + argc);
	print("argv = " + argv);

	//assert( TestCase1() );
}

private bool TestCase1() const {
	int bla const = 1;

	ModifyInt(bla);

	return false;
}

private void ModifyInt(int value ref) const {
	value = value++;
}


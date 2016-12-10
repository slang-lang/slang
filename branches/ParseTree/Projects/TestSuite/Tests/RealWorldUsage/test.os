#!/usr/local/bin/oscript

// Library includes
import System.All;

// Project includes
import imported.DerivedObjectImported;
import imported.ThirdLevelImported;

private bool flag;

private bool test() {
	print("test");

	flag = true;

	return true;
}

private void SingleMethod() {
	writeln("SingleMethod()");
	writeln("flag = " + flag);

	test();

	writeln("flag = " + flag);
}

private int member final;

public void Main(int argc, string argv) {
	member = 1;

	doIt();
}

private void doIt() {
	BaseObjectImported baseobj = new BaseObjectImported();
	DerivedObjectImported derivedobj = new DerivedObjectImported();
	ThirdLevelImported thirdobj = new ThirdLevelImported();

	writeln("baseobj = " + baseobj.ToString());
	writeln("derivedobj = " + derivedobj.ToString());
	writeln("thirdobj = " + thirdobj.ToString());

	SingleMethod();

	print("3^2 = " + Math.power(3));
	print("3^2 = " + Math.power(3, 2));

	print("abs(-3) = " + abs(-3));

       	assert(flag);
}


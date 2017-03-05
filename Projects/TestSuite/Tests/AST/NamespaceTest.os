#!/usr/local/bin/oscript

private namespace Space {
	public int mValue = 1;

	public void SpacedMethod() {
		print("Space.SpacedMethod()");
	}
}

public void Main(int argc = 0, string args = "") {
	print("AST namespace test");

	int i = 17;
	print("i = " + i);

	print("Space.mValue = " + Space.mValue);

	Space.SpacedMethod();
}


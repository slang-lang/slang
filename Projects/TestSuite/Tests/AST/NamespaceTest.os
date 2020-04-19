#!/usr/local/bin/slang

private namespace Space {
	public int mValue = 1;

	public void SpacedMethod() {
		print("Space.SpacedMethod()");
	}

	public int SpacedMethod(int value) {
		print("Space.SpacedMethod(" + value + ")");

		mValue = value;

		return mValue;
	}
}

public void Main(int argc = 0, string args = "") {
	print("AST namespace test");

	int i = 17;
	print("i = " + i);

	print("Space.mValue = " + Space.mValue);

	Space.SpacedMethod();

	print("bla");

	Space.SpacedMethod(17);
}


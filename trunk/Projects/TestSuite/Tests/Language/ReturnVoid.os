#!/usr/local/bin/oscript

public void Main(int argc, string args) {
	var i = 173;

	print("i = " + i);
	doSomething(i);
	print("i = " + i);
}

private void doSomething(int value modify ref) {
	value += 1;

	return PrintText();
}

private void PrintText() {
	print("Text");
}


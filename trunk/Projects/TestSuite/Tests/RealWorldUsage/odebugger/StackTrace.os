#!/usr/local/bin/oscript

public void Main(int argc, string args) {
	int stack;

	print("Frame " + stack);

	Stack(stack + 1);
}

void Stack(int stack) {
	print("Frame " + stack);

	if ( stack >= 10 ) {
		return;
	}

	Stack(stack + 1);
}


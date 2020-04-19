#!/usr/local/bin/slang

public void Main(int argc, string args) {
	//int i ref;		// this fails
	//int i ref = 2;	// this fails
	int i ref = new int(2);	// this is correct
	print("i = " + i);

	i += 1;
	print("i = " + i);

	MethodCall(i);
	print("i = " + i);
}

private void MethodCall(int value ref) {
	value +=1;
}


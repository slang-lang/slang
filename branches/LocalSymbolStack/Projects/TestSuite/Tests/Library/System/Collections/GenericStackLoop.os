#!/usr/local/bin/oscript

import System.Collections.GenericStack;
import System.String;

public void Main(int argc = 0, string args = "") {
	GenericStack<String> stack = new GenericStack<String>();

	for ( int i = 0; i < 100; i = i++ ) {
		stack.push(new String("String(" + i + ")"));
	}

	loop(stack);
}

private void loop(GenericStack<String> collection) const {
	int count = 0;

	while ( count < 10 ) {
		print("count = " + count);

		GenericIterator<String> it = collection.getIterator();

		while ( it.hasNext() ) {
			it.next();

			//print(string it.current());
		}

		count++;
	}
}


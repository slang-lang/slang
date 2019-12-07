#!/usr/local/bin/oscript

import System.Collections.Queue;
import System.String;

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
	assert( TestCase5() );	// this test should fail
	assert( TestCase6() );
}

public bool TestCase1() {
	print("TestCase 1: Queue.enqueue()");

	Queue<String> queue = new Queue<String>();
	assert( queue );
	assert( queue is ICollection );

	assert( queue.empty() );

	queue.enqueue(new String("Entry 1"));
	queue.enqueue(new String("Entry 2"));
	queue.enqueue(new String("Entry 3"));

	assert( !queue.empty() );
	assert( queue.size() == 3 );

	foreach ( Object e : queue ) {
		//print(string e);
	}

	return true;
}

private bool TestCase2() {
	print("TestCase 2: Queue.dequeue()");

	Queue<String> queue = new Queue<String>();
	assert( queue );
	assert( queue is ICollection );

	assert( queue.empty() );

	queue.enqueue(new String("Entry 1"));
	queue.enqueue(new String("Entry 2"));
	queue.enqueue(new String("Entry 3"));

	assert( !queue.empty() );
	assert( queue.size() == 3 );

	while ( !queue.empty() ) {
		String item = queue.dequeue();
		//print(string item);
	}

	return queue.empty();
}

private bool TestCase3() {
	print("TestCase 3: Queue.peek()");

	Queue<String> queue = new Queue<String>();
	assert( queue );
	assert( queue is ICollection );

	assert( queue.empty() );

	queue.enqueue(new String("Entry 1"));

	//print(string queue.peek());
	assert( queue.peek() == "Entry 1");

	queue.enqueue(new String("Entry 2"));

	//print(string queue.peek());
	assert( queue.peek() == "Entry 2");

	queue.enqueue(new String("Entry 3"));

	//print(string queue.peek());
	assert( queue.peek() == "Entry 3");

	assert( !queue.empty() );
	assert( queue.size() == 3 );

	return true;
}

private bool TestCase4() {
	print("TestCase 4: Queue.clear()");

	Queue<String> queue = new Queue<String>();
	assert( queue );
	assert( queue is ICollection );

	assert( queue.empty() );

	queue.enqueue(new String("Entry 1"));
	queue.enqueue(new String("Entry 2"));
	queue.enqueue(new String("Entry 3"));

	assert( !queue.empty() );
	assert( queue.size() == 3 );

	foreach ( String s : queue ) {
		//print("s = " + s);
	}

	queue.clear();

	assert( queue.empty() );
	assert( queue.size() == 0);

	foreach ( String t : queue ) {
		assert( false );
	}

	return true;
}

private bool TestCase5() {
	print("TestCase 5: native data types");

	try {
		Queue<string> queue = new Queue<string>();

		assert( queue );
		assert( queue is Object );

		queue.enqueue("1");
		queue.enqueue("2");
		queue.enqueue("3");

		assert( queue.size() == 3 );

		Iterator<string> it = queue.getIterator();
		while ( it.hasNext() ) {
			it.next();

			string value = it.current();
			//print(value);
		}

		queue.clear();

		assert( queue.empty() );

		return true;
	}
	catch {
		return false;
	}

	return false;
}

private bool TestCase6() {
	print("TestCase 6: Queue.at()");

	Queue<string> queue = new Queue<string>();

	assert( queue );
	assert( queue is Object );
	assert( queue is ICollection );

	queue.enqueue("1");
	queue.enqueue("2");
	queue.enqueue("3");

	assert( queue.size() == 3 );

	assert( queue.at(0) == "1" );
	assert( queue.at(1) == "2" );
	assert( queue.at(2) == "3" );

	return true;
}


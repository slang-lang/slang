#!/usr/local/bin/oscript

import System.Collections.Queue;
import System.String;

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
}

public bool TestCase1() {
	print("TestCase 1: Queue.enqueue()");

	Queue<String> queue = new Queue<String>();
	assert( queue );
	assert( queue is IIterateable );

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
	assert( queue is IIterateable );

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
	assert( queue is IIterateable );

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


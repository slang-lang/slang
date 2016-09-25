#!/usr/local/bin/oscript

public object Main {
	public void Main(int argc, string args) {
		assert( TestCase1() );
	}

	private bool TestCase1() const {
		writeln("TestCase1: exit");

		exit;

		assert(!"this should not happen");
	}
}


#!/usr/local/bin/oscript

public void Main(int argc, string args) {
	assert( TestCase1() );
}

private bool TestCase1() const {
	int time = 173;

	print("sleeping for " + time + "ms...");

	sleep(time);

	return true;
}


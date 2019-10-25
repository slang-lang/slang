#!/usr/local/bin/oscript

public void Main(int argc = 0, string args = "") modify {
	print("Starting endless loop with sleep(1)");

	bool run = true;

	while ( run ) {
		sleep(1);
	}

	print("Finished endless loop...?");
}


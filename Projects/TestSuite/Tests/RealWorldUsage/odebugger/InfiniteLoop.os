#!/usr/local/bin/slang

public void Main(int argc, string args) {
	bool run = true;

	print("Starting infinite loop...");

	while ( run ) {
		idle();
	}

	print("Finished inifinite loop.");
}

private void idle() {
	// do nothing
}


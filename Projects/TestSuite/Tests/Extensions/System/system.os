#!/usr/bin/env slang

public void Main(int argc, string args) {
	string result = system("ls -la");

	print(result);
}


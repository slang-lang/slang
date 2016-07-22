#!/usr/local/bin/oscript

import System.IO.Logger;

public object Main {
	public void Main(int argc, string args) {
		System.IO.Logger logger = new System.IO.Logger("MainObjectAndSomeOtherShit", 12);

		logger.debug("this is a debug output");
	}
}


#!/usr/local/bin/oscript

import System.Logger;

public object Main {
	public void Main(int argc, string args) {
		System.Logger logger = new System.Logger("MainObjectAndSomeOtherShit", 8);

		logger.debug("this is a debug output");
	}
}


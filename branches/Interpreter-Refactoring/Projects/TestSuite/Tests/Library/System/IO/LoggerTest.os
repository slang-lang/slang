#!/usr/local/bin/oscript

import System.IO.Logger;

public void Main(int argc = 0, string args = "") {
	System.IO.Logger logger = new System.IO.Logger("MainObjectAndSomeOtherStuff", 12);

	logger.debug("this is a debug output");
	logger.error("this is an error");
	logger.info("this is an information");
	logger.warning("this is a warning");
}


#!/usr/local/bin/oscript

import liblog.StdOutLogger;

public void Main(int argc, string args) {
	StdOutLogger logger = new StdOutLogger(ILogger null, "Main");

	logger.debug("This is a debug message");
	logger.error("This is an error message");
	logger.info("This is an info message");
	logger.warning("This is a warning message");

	StdOutLogger sub = new StdOutLogger(ILogger, "Sub");
	sub.debug("Another debug message");

	logger.fatal("This is a fatal message (execution should stop now)");

	assert( !"we should not get here" );
}


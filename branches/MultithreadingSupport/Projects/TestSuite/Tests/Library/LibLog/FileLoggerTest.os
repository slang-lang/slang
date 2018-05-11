#!/usr/local/bin/oscript

import LibLog.FileLogger;

public object LoggingObject {
	private ILogger mLogger;

	public void Constructor(ILogger logger) {
		mLogger = ILogger new FileLogger(logger, "LoggingObject");

		mLogger.info("Constructor()");
	}

	public void Destructor() {
		mLogger.info("Destructor()");
	}
}

public void Main(int argc, string args) {
	try {
		ILogger logger = ILogger new FileLogger("Test.log", "Logger");

		LoggingObject obj = new LoggingObject(logger);

		logger.debug("Debug message");
		logger.error("Error message");
		logger.info("Info message");
		logger.warning("Warning message");
		logger.fatal("Fatal message");

		logger.info("This message should not be written");
	}
	catch ( string e ) {
		print("e = " + e);
	}
	catch ( IException e ) {
		print("e.what() = " + e.what());
	}
}


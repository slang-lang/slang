#!/usr/local/bin/oscript

import LibLog.LibLog;

public object LoggingObject {
	private Logger mLogger;

	public void Constructor(ILogger logger) {
		mLogger = new Logger(logger, "LoggingObject");

		mLogger.info("Constructor()");
	}

	public void Destructor() {
		mLogger.info("Destructor()");
	}
}

public int Main(int argc, string args) {
	try {
		ILogger logger = ILogger new StdOutLogger("Logger", 10);

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

	return 0;
}


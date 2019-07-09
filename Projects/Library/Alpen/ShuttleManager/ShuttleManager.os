
// library imports
import libLog.Logger;

// project imports
import libs.Consts;
import libs.IPCService;


public object ShuttleManager {
	public void Constructor(Logger logger) {
		mLogger = logger;

		mLogger.info("Constructor()");
	}

	public void Destructor() {
		mLogger.info("Destructor()");
	}


	private Logger mLogger;
}


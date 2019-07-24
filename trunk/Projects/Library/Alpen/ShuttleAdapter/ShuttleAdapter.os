
// library imports
import libLog.Logger;

// project imports
import libs.Consts;
import libs.IPCService;
import libs.Telegrams.All;


public object ShuttleAdapter {
	public void Constructor(ILogger logger, IPCService ipcService) {
		mIPCService = ipcService;
		mLogger = new Logger(logger, "ShuttleAdapter");

		mLogger.info("Constructor()");
	}

	public void Destructor() {
		mLogger.info("Destructor()");
	}

	private IPCService mIPCService;
	private Logger mLogger;
}


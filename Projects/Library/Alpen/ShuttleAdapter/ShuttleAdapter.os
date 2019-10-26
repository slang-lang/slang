
// library imports
import libLog.Logger;
import System.IO.File;

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

		shutdown();
	}

	public void init() modify {
		// open connection to subsystem
		connect();
	}

	public void process(IPCMessage msg = null) modify {
		mLogger.info("Processing...");

		// send message (if available)
		if ( msg ) {
			sendMessage(msg);
		}

		// receive messages
		string telegram;
		while ( (telegram = receive()) != "" ) {
			notifyShuttleManager(telegram);
		}
	}

	private void connect() modify {
		mLogger.info("Connecting to subsystem...");

		mLogger.info("Connected to subsystem.");
	}

	private void disconnect() modify {
		mLogger.info("Disconnecting from subsystem...");

		mLogger.info("Disconnected from subsystem.");
	}

	private void notifyShuttleManager(string message) modify {
		mIPCService.send(SHUTTLEMANAGER_QUEUE, message);
	}

	private string receive() modify {
		mLogger.debug("Receiving telegram...");

		try {
			var file = new System.IO.File("telegram.txt", System.IO.FileAccessMode.ReadWrite);

			string telegram;
			while ( !file.isEOF() ) {
				var c = file.readChar();

				if ( c == LINEBREAK ) {
					break;
				}

				telegram += c;
			}

			file.rewind();
			file.write(LINEBREAK);

			mLogger.debug("received telegram <" + telegram + ">");

			return telegram;
		}

		return "";
	}

	private void sendMessage(IPCMessage msg) modify {
		mLogger.info("sending telegram <" + msg.message + ">");
	}

	private void shutdown() modify {
		mLogger.info("Shutting down...");

		disconnect();
	}

	private IPCService mIPCService;
	private Logger mLogger;
}


#!/usr/local/bin/slang

// library imports
import libLog.Logger;
import libLog.StdOutLogger;
import libParam.ParameterHandler;

// project imports
import libs.Consts;
import libs.Database;
import libs.IPCService;
import ShuttleAdapter;


public void Main(int argc, string args) {
    var params = new ParameterHandler(argc, args);
    if ( params.contains("version") ) {
        print("Alpen ShuttleAdapter Version 0.0.0");
        return;
    }

    try {
        var logger = ILogger new StdOutLogger("Main", 20);

        logger.info("Connecting to database...");

        DB.Connect();

        logger.info("Connecting to IPC queue...");

        var ipcService = new IPCService(SHUTTLEADAPTER_QUEUE, SHUTTLEADAPTER);

	    logger.info("Starting ShuttleAdapter...");

        var shuttleAdapter = new ShuttleAdapter(logger, ipcService);
	    shuttleAdapter.init();

        IPCMessage msg;

        bool running = true;
        while ( running ) {
            shuttleAdapter.process(msg);

            int counter;
            while ( counter < DISPATCH_MESSAGE_RETRIES / 2) {
                logger.info("Waiting for new telegrams...");

                if ( (msg = ipcService.receive()) != null ) {
                    logger.info("IPCMessage received: " + cast<string>(msg));

                    if ( msg.message == MSG_SHUTDOWN ) {
                        running = false;
                    }

                    break;
                }

                sleep( DISPATCH_WAIT_TIME );
                counter++;
            }
        }

        logger.info("Shutting down...");
        logger.info("Disconnecting from database...");

        DB.Disconnect();
    }
    catch ( string e ) {
        print("Exception: " + e);
    }
    catch ( IException e ) {
        print("Exception: " + e.what());
    }
}


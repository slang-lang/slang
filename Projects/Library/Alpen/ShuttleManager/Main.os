#!/usr/bin/env slang

// library imports
import libLog.Logger;
import libLog.StdOutLogger;
import libParam.ParameterHandler;

// project imports
import libs.Consts;
import libs.Database;
import libs.IPCService;
import ShuttleManager;


public void Main(int argc, string args) {
    var params = new ParameterHandler(argc, args);
    if ( params.contains("version") ) {
        print("Alpen ShuttleManager Version 0.0.1");
        return;
    }

    try {
        var logger = ILogger new StdOutLogger("Main", 20);

        logger.info("Connecting to database...");

        DB.Connect();

        logger.info("Connecting to IPC queue...");

        var ipcService = new IPCService(SHUTTLEMANAGER_QUEUE, SHUTTLEMANAGER);

        logger.info("Starting ShuttleManager...");

        var shuttleManager = new ShuttleManager(logger, ipcService);


        IPCMessage msg;

        bool running = true;
        while ( running ) {
            shuttleManager.process(msg);

            int counter;
            while ( counter < DISPATCH_MESSAGE_RETRIES ) {
                logger.info("Waiting for new orders...");

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


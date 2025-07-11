#!/usr/bin/env slang

// library imports
import libLog.Logger;
import libLog.StdOutLogger;
import libParam.ParameterHandler;

// project imports
import libs.Consts;
import libs.Database;
import libs.IPCService;


public void Main(int argc, string args) {
    var params = new ParameterHandler(argc, args);
    if ( params.contains("version") ) {
        print("Alpen StationManager Version 0.0.0");
        return;
    }

    try {
        var logger = ILogger new StdOutLogger("Main", 20);

        logger.info("Connecting to database...");

        DB.Connect();

        logger.info("Connecting to IPC queue...");

        var ipcService = new IPCService(STATIONMANAGER_QUEUE, STATIONMANAGER);
        //var shuttleManager = new ShuttleManager(logger, ipcService);

        IPCMessage message;

        bool running = true;
        while ( running ) {
            //shuttleManager.process();

            int counter;
            while ( counter < DISPATCH_MESSAGE_RETRIES ) {
                logger.info("Waiting for new orders...");

                if ( (message = ipcService.receive()) != null ) {
                    logger.info("IPCMessage received: " + cast<string>(message));

                    if ( message.message == MSG_SHUTDOWN ) {
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


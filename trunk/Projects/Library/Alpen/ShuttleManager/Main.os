#!/usr/local/bin/oscript

// library imports
import libLog.StdOutLogger;

// project imports
import libs.Consts;
import libs.Database;
import libs.IPCService;
import ShuttleManager;


public void Main(int argc, string args) {
    try {
        var logger = new StdOutLogger("Main", 15);

        logger.info("Connecting to database...");
        DB.Connect();

        logger.info("Connecting to IPC queue...");

        var ipcService = new IPCService(SHUTTLEMANAGER_QUEUE, SHUTTLEMANAGER);
        var shuttleManager = new ShuttleManager(cast<ILogger>(logger), ipcService);

        bool running = true;

        while ( running ) {
            shuttleManager.process();

            int counter;
            IPCMessage message;

            while ( counter < 10 ) {
                logger.info("Waiting for new orders...");

                message = ipcService.receive();
                if ( message ) {
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

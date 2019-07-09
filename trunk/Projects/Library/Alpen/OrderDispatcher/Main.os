#!/usr/local/bin/oscript

// library imports
import libLog.StdOutLogger;

// project imports
import libs.Consts;
import libs.Database;
import libs.IPCService;
import OrderDispatcher;


public void Main(int argc, string args) {
    try {
        var logger = new StdOutLogger("Main", 15);

        logger.info("Connecting to database...");
        DB.Connect();

        logger.info("Connecting to IPC queue...");

        var dispatcher = new OrderDispatcher(Logger logger);
        var ipcService = new IPCService(ORDERDISPATCHER_QUEUE, ORDERDISPATCHER);

        bool running = true;

        while ( running ) {
            dispatcher.dispatch();

            int counter;
            IPCMessage message;

            while ( counter < 10 ) {
                logger.info("Waiting for new orders...");

                message = ipcService.receive();
                if ( message ) {
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


#!/usr/local/bin/oscript

// library imports
import libLog.StdOutLogger;

// project imports
import libs.Database;
import libs.IPCService;
import Dispatcher;


public void Main(int argc, string args) {
    try {
        DB.Connect();

        var logger = new StdOutLogger("Main", 15);
        var dispatcher = new Dispatcher(new Logger(cast<ILogger>(logger), "OrderDispatcher"));
	var ipcService = new IPCService(ORDERDISPATCHER_QUEUE, ORDERDISPATCHER, true);

        while ( true ) {
            dispatcher.dispatch();

            int counter;
            IPCMessage message;

            while ( counter < 10 ) {
                logger.info("Waiting for new orders...");

                message = ipcService.receive();
		if ( message ) {
			if ( message.message == MSG_SHUTDOWN ) {
				return;
			}

			break;
		}

                sleep( 1000 );
                counter++;
            }
        }

        DB.Disconnect();
    }
    catch ( string e ) {
        print("Exception: " + e);
    }
    catch ( IException e ) {
        print("Exception: " + e.what());
    }
}


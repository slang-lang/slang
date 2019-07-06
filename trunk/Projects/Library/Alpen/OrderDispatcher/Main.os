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
        var dispatcher = new Dispatcher( new Logger(cast<ILogger>(logger), "OrderDispatcher") );
	var ipcService = new IPCService( ORDERDISPATCHER );

        while ( true ) {
            dispatcher.dispatch();

            logger.info("Waiting for new orders...");
            //sleep(5000);

            while ( !ipcService.receive() ) {
                sleep( 100 );
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


#!/usr/local/bin/oscript

// library imports
import libLog.StdOutLogger;

// project imports
import libs.Database;
import Dispatcher;


public void Main(int argc, string args) {
    try {
        var logger = new StdOutLogger("Main");

        DB.Connect();

        var dispatcher = new Dispatcher(cast<ILogger>( new Logger(cast<ILogger>(logger), "OrderDispatcher") ), DB.Handle);

        while ( true ) {
            dispatcher.dispatch();

            logger.info("Waiting for new orders...");
            sleep(5000);
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

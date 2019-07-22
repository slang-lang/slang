#!/usr/local/bin/oscript

// library imports
import libLog.FileLogger;
import libLog.StdOutLogger;

// project imports
import libs.IPCService;


public void Main(int argc, string args) {
	// open System V message queues for all processes (including ourself)

	var logger = new StdOutLogger("Main", 20);
	//var logger = new FileLogger("MessageBroker.log", "Main", 20);

	logger.info("Opening message queues...");
	var self = new IPCService(MESSAGEBROKER_QUEUE, MESSAGEBROKER, true);
	var orderDispatcher = new IPCService(ORDERDISPATCHER_QUEUE, ORDERDISPATCHER, true);
	var shuttleAdatpter = new IPCService(SHUTTLEADAPTER_QUEUE, SHUTTLEADAPTER, true);
	var shuttleManager = new IPCService(SHUTTLEMANAGER_QUEUE, SHUTTLEMANAGER, true);
	var stationManager = new IPCService(STATIONMANAGER_QUEUE, STATIONMANAGER, true);

	IPCMessage message;
	while ( true ) {
		if ( (message = self.receive()) != null ) {
			logger.info("Received: " + cast<string>( message ));

			if ( message.message == MSG_SHUTDOWN ) {
				break;
			}
		}

		sleep(100);
	}

	logger.info("Closing message queues...");
}


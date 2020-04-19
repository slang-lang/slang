#!/usr/local/bin/slang

// library imports
import libLog.Logger;
import libLog.StdOutLogger;
import libParam.ParameterHandler;

// project imports
import libs.IPCService;


/*
 * open System V message queues for all processes (including ourself)
 */

public void Main(int argc, string args) {
	var params = new ParameterHandler(argc, args);
	if ( params.contains("version") ) {
		print("Alpen MessageBroker Version 0.1.0");
		return;
	}


	var logger = new StdOutLogger("Main", 20);
	//var logger = new FileLogger("MessageBroker.log", "Main", 20);

	logger.info("Opening message queues...");

	var self = new IPCService(MESSAGEBROKER_QUEUE, MESSAGEBROKER, true);
	var orderDispatcher = new IPCService(ORDERDISPATCHER_QUEUE, ORDERDISPATCHER, true);
	var shuttleAdatpter = new IPCService(SHUTTLEADAPTER_QUEUE, SHUTTLEADAPTER, true);
	var shuttleManager = new IPCService(SHUTTLEMANAGER_QUEUE, SHUTTLEMANAGER, true);
	var stationManager = new IPCService(STATIONMANAGER_QUEUE, STATIONMANAGER, true);

	IPCMessage msg;
	while ( true ) {
		if ( (msg = self.receive()) != null ) {
			logger.info("Received: " + cast<string>( msg ));

			if ( msg.message == MSG_SHUTDOWN ) {
				break;
			}
		}

		sleep(100);
	}

	logger.info("Closing message queues...");
}


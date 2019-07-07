#!/usr/local/bin/oscript

import libParam.ParameterHandler;


public void Main(int argc, string args) {
	var params = new ParameterHandler(argc, args);
	if ( params.empty() ) {
		print("usage: <program> <message queue> <message>");
		return;
	}

	int queueID = cast<int>( params.at(0).Key );
	string message = params.at(1).Key;

	print("Sending \"" + message + "\" to queue \"" + queueID + "\"");

	int handle = msgget(queueID);
	msgsnd(handle, "{\"message\":\"" + message + "\",\"receiver\":" + queueID + "}");
}


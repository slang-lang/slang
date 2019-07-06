
// library imports

// project imports
import Database;


public string ORDERDISPATCHER const = "ORDERDISPATCHER";
public string SHUTTLEADAPTER const = "SHUTTLEADAPTER";
public string SHUTTLEMANAGER const = "SHUTTLEMANAGER";
public string STATIONMANAGER const = "STATIONMANAGER";


public object IPCMessage {
	public string message;
	public int messageID;
	public string receiver;
	public string sender;

	public void Constructor() {
		// nothing to do here
	}

	public void Constructor(string _sender, string _receiver, int _messageID, string _message) {
		message = _message;
		messageID = _messageID;
		receiver = _receiver;
		sender = _sender;
	}

	public string =operator(string) const {
		return "IPCMessage: {" +
			"sender: \"" + sender + "\", " +
			"receiver: \"" + receiver + "\", " +
			"messageID: " + messageID + ", " +
			"message: \"" + message + " " +
			"}";
	}
}

public interface IIPCReceiver {
	public IPCMessage receive() modify;
}

public interface IIPCSender {
	public void send(IPCMessage) modify;
	public void send(string receiver, string message) modify;
}

public object IPCService implements IIPCReceiver, IIPCSender {
	public void Constructor(string processName) {
		mProcessName = processName;
	}

	public IPCMessage receive() modify {
		IPCMessage message;

		int result = DB.Query( "SELECT * FROM ipc_queue WHERE receiver = '" + mProcessName + "' AND received IS NULL" );
		if ( result ) {
			message = new IPCMessage(
				mysql_get_field_value(result, "sender"),
				mysql_get_field_value(result, "receiver"),
				cast<int>( mysql_get_field_value(result, "message_id") ),
				mysql_get_field_value(result, "message")
			);

			DB.Update( "UPDATE ipc_queue SET received = NOW() WHERE message_id = " + message.messageID );
		}

		return message;
	}

	public void send(IPCMessage message) modify {
		send( message.receiver, message.message );
	}

	public void send(string receiver, string message) modify {
		DB.Insert( "INSERT INTO ipc_queue (sender, receiver, message, created) VALUES ('" + mProcessName + "', '" + receiver + "', '" + message + "', NOW())" );
	}

	private string mProcessName;
}



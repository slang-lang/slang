
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
		var message = new IPCMessage();

		return message;
	}

	public void send(IPCMessage message) modify {
		print("send(" + cast<string>( message ) + ")");
	}

	public void send(string receiver, string message) modify {
		send( new IPCMessage(mProcessName, receiver, 0, message) );
	}

	private string mProcessName;
}



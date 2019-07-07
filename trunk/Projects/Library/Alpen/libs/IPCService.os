
// library imports

// project imports
import Database;


public string MESSAGEBROKER const = "MESSAGEBROKER";
public int MESSAGEBROKER_QUEUE const = 655361;
public string ORDERDISPATCHER const = "ORDERDISPATCHER";
public int ORDERDISPATCHER_QUEUE const = 655362;
public string SHUTTLEADAPTER const = "SHUTTLEADAPTER";
public int SHUTTLEADAPTER_QUEUE const = 655363;
public string SHUTTLEMANAGER const = "SHUTTLEMANAGER";
public int SHUTTLEMANAGER_QUEUE const = 655364;
public string STATIONMANAGER const = "STATIONMANAGER";
public int STATIONMANAGER_QUEUE const = 655365;


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
			"message: \"" + message + "\" " +
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
	public void Constructor(int queueID, string processName, bool create = false) {
		mProcessName = processName;
		mQueueHandle = msgget(queueID, create);
		mQueueOwner = create;
	}

	public void Destructor() {
		if ( mQueueOwner ) {
			msgctl(mQueueHandle);
		}
	}

	public IPCMessage receive() modify {
		string msg = msgrcv(mQueueHandle);
		if ( msg ) {
			var message = new IPCMessage();

			// unserialize JSON message
			FromJsonString(message, msg);

			return message;
		}

		return IPCMessage null;
	}

	public bool send(IPCMessage message) modify {
		string msg = ToJsonString(message);

		return msgsnd(mQueueHandle, msg) != -1;
	}

	public bool send(string receiver, string message) modify {
		return send( new IPCMessage(mProcessName, receiver, 0, message) );
	}

	private string mProcessName;
	private int mQueueHandle;
	private bool mQueueOwner;
}



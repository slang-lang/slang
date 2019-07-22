
// library imports
import System.Collections.Map;

// project imports
import Consts;
import Database;


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

	public string toString() const {
		return "{ \"sender\": \"" + sender + "\", \"receiver\": \"" + receiver + "\", \"messageID\": " + messageID + ", \"message\": \"" + message + "\" }";
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
	public void Constructor(int queueID, string processName, bool isOwner = false) {
		mConnectedQueues = new Map<int, int>();
		mProcessName = processName;
		mQueueHandle = msgget(queueID, isOwner);
		mQueueOwner = isOwner;
	}

	public void Destructor() {
		if ( mQueueOwner ) {
			msgctl(mQueueHandle);
		}
	}

	public bool connect(int queueID) modify {
		if ( mConnectedQueues.contains(queueID) ) {
			mConnectedQueues.remove(queueID);
		}

		mConnectedQueues.insert(queueID, msgget(queueID));

		return mConnectedQueues[queueID] != -1;
	}

	public IPCMessage receive(bool waitForMessage = false) modify {
		string msg = msgrcv(mQueueHandle, waitForMessage);
		if ( msg ) {
			var message = new IPCMessage();

			// unserialize JSON message
			FromJsonString(message, msg);

			return message;
		}

		return IPCMessage null;
	}

	public bool send(int queueID, IPCMessage message) modify {
		//string msg = ToJsonString(message);
		string msg = message.toString();

		return msgsnd(queueID, msg) != -1;
	}

	public bool send(int queueID, string message) modify {
		return send( queueID, new IPCMessage(mProcessName, "", 0, message) );
	}

	private Map<int, int> mConnectedQueues;
	private string mProcessName;
	private int mQueueHandle;
	private bool mQueueOwner;
}




// library imports

// project imports


public object IPCMessage {
    public string message;
    public int messageID;
    public string receiver;
    public string sender;
}


public object IPCReceiver {
    public string mReceiver const;

    public void Constructor(string receiver) {
        mReceiver = receiver;
    }
}

public object IPCSender {
    public string mSender const;

    public void Constructor(string sender) {
        mSender = sender;
    }
}


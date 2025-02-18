

public object IPCMessage const {
	public string Message const;
	public string Receiver const;
	public string Sender const;

	public void Constructor( string sender, string receiver, string message ) {
		Message  = message;
		Receiver = receiver;
		Sender   = sender;
	}

	public string =operator( string ) const {
		return "{ Sender: \"" + Sender + "\", Receiver: \"" + Receiver + "\", Message: \"" + Message + "\" }";
	}
}


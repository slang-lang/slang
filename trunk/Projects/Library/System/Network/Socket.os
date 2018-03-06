
public namespace System.Network { }

public stable interface ISocketAddress {
	// this is empty by intend
}

public object IPv4Address const implements ISocketAddress {
	public string _sa_address const;
	public int _sa_port const;
	public int _sa_family const;

	public void Constructor(string address, int port) {
		_sa_address = address ? address : INADDR_ANY;
		_sa_family = AF_INET;
		_sa_port = port;
	}
}

public object IPv6Address const implements ISocketAddress {
	public string _sa_address const;
	public int _sa_port const;
	public int _sa_family const;

	public void Constructor(string address, int port) {
		_sa_address = address ? address : INADDR_ANY;
		_sa_family = AF_INET6;
		_sa_port = port;
	}
}


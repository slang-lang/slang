
public interface ISocketAddress {
	// this is empty by intend
}

public object IPv4Address const implements ISocketAddress {
	public string _address const;
	public int _port const;
	public int _sa_family const;

	public void Constructor(string address, int port) {
		_address = address;
		_port = port;
		_sa_family = AF_INET;
	}
}

public object IPv6Address const implements ISocketAddress {
	public string _address const;
	public int _port const;
	public int _sa_family const;

	public void Constructor(string address, int port) {
		_address = address;
		_port = port;
		_sa_family = AF_INET6;
	}
}

public object Socket {
	public void Constructor() {
	}

	public void Destructor() {
	}
}


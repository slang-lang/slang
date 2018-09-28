
import Exception;
import Socket;

public namespace System.Network { }

public object ClientSocket {
	private IPv4Address mEndPoint;
	private bool mIsConnected;
	private int mSocket;

	public void Constructor() {
		mIsConnected = false;

		Init();
	}

	public void Constructor(IPv4Address endpoint ref) {
		mEndPoint = endpoint;

		Constructor();
	}

	public void Constructor(string address, int port) {
		Constructor(new IPv4Address(address, port));
	}

	public void Close() modify {
		if ( mIsConnected ) {
			close(mSocket);

			mIsConnected = false;
		}
	}

	public bool Connect() modify throws {
		if ( !mEndPoint ) {
			throw new Exception("invalid endpoint");
		}

		return Connect(mEndPoint);
	}

	public bool Connect(IPv4Address endpoint ref) modify {
		if ( endpoint ) {
			mEndPoint = endpoint;
		}

		mIsConnected = connect(mSocket, ISocketAddress mEndPoint) != -1;
		return mIsConnected;
	}

	public bool Connect(string address, int port) modify {
		return Connect(new IPv4Address(address, port));
	}

	private void Init() modify throws {
		mSocket = socket(AF_INET, SOCK_STREAM, 0);

		if ( mSocket == -1 ) {
			throw new Exception("socket initialisation failed");
		}
	}

	public bool IsConnected() const {
		return mIsConnected;
	}

	public void Write(bool data) throws {
		if ( !mIsConnected ) {
			throw new Exception("not connected");
		}

		writeb(mSocket, data);
	}

	public void Write(double data) throws {
		if ( !mIsConnected ) {
			throw new Exception("not connected");
		}

		writed(mSocket, data);
	}

	public void Write(float data) throws {
		if ( !mIsConnected ) {
			throw new Exception("not connected");
		}

		writef(mSocket, data);
	}

	public void Write(int data) throws {
		if ( !mIsConnected ) {
			throw new Exception("not connected");
		}

		writei(mSocket, data);
	}

	public void Write(string data) throws {
		if ( !mIsConnected ) {
			throw new Exception("not connected");
		}

		writes(mSocket, data);
	}
}


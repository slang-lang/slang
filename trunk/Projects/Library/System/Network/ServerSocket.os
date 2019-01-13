
import Exception;
import Socket;

// declare 'System.Network' namespace to prevent a user defined private 'System.Network' namespace
public namespace System.Network { }

public object ServerSocket {
	/*
	 * Public constants
	 */
	public int DEFAULT_QUEUE_LENGTH const = 50;

	/*
	 * Default constructor
	 */
	public void Constructor() {
		mQueueLength = DEFAULT_QUEUE_LENGTH;

		Init();
	}

	/*
	 * Constructs a server socket object by using the given port
	 */
	public void Constructor(int port) {
		mEndpoint = new IPv4Address(INADDR_ANY, port);

		Constructor(mEndpoint, DEFAULT_QUEUE_LENGTH);
	}

	/*
	 * Constructs a server socket object by using the given port with a given queue length
	 */
	public void Constructor(int port, int queueLength) {
		mEndpoint = new IPv4Address(INADDR_ANY, port);
		mQueueLength = queueLength;

		Constructor(mEndpoint, mQueueLength);
	}

	/*
	 * Constructs a server socket object by using a given IPv4 address with a given queue length
	 */
	public void Constructor(IPv4Address address, int queueLength) {
		mEndpoint = address;
		mQueueLength = queueLength;

		Init();
	}

	/*
	 * Destructor
	 */
	public void Destructor() {
		Close();
	}

	/*
	 * Listens for a connection to be made to this socket and accepts it.
	 * The method blocks until a connection is made.
	 */
	public bool Accept() modify throws {
		mListenerSocket = accept(mMasterSocket);

		return mListenerSocket > 0;
	}

	/*
	 * Binds the ServerSocket to the address given during object construction
	 */
	public bool Bind() modify throws {
		if ( !mEndpoint ) {
			throw new Exception("endpoint not set");
		}

		return bind(mMasterSocket, ISocketAddress mEndpoint) > 0;
	}

	/*
	 * Binds the ServerSocket to the given address
	 */
	public bool Bind(IPv4Address endpoint) modify throws {
		if ( !endpoint ) {
			throw new Exception("endpoint not set");
		}

		mEndpoint = endpoint;

		return Bind();
	}

	/*
	 * Closes this socket
	 */
	public bool Close() throws {
	    return close(mMasterSocket) == 0;
	}

	/*
	 * Returns the endpoint address on which the server is listening as string
	 */
	public string getAddress() const {
		if ( !mEndpoint ) {
			return "";
		}

		return mEndpoint._sa_address;
	}

	/*
	 * Returns the port on which the socket is listening
	 */
	public int getPort() const {
		if ( !mEndpoint ) {
			return 0;
		}

		return mEndpoint._sa_port;
	}

	private void Init() modify {
	    mMasterSocket = socket(AF_INET, SOCK_STREAM, 0);
	}

	public int Listen() modify {
	    return listen(mMasterSocket, mQueueLength);
	}

	public bool ReadBool() const throws {
		if ( !mListenerSocket ) {
			throw new Exception("not connected");
		}

		return readb(mListenerSocket);
	}

	public double ReadDouble() const throws {
		if ( !mListenerSocket ) {
			throw new Exception("not connected");
		}

		return readd(mListenerSocket);
	}

	public float ReadFloat() const throws {
		if ( !mListenerSocket ) {
			throw new Exception("not connected");
		}

		return readf(mListenerSocket);
	}

	public int ReadInt() const throws {
		if ( !mListenerSocket ) {
			throw new Exception("not connected");
		}

		return readi(mListenerSocket);
	}

	public string ReadString(int length = 1) const throws {
		if ( !mListenerSocket ) {
			throw new Exception("not connected");
		}

	    return reads(mListenerSocket, length);
	}

	/*
	 * Private members
	 */
	private IPv4Address mEndpoint;
	private int mListenerSocket = 0;
	private int mMasterSocket;
	private int mQueueLength;
}



import System.Exception;
import System.Network.Socket;

public namespace System.Network { }

public object ServerSocket {
	/*
	 * Public constants
	 */
	public int DEFAULT_QUEUE_LENGTH const = 50;

	/*
	 * Private members
	 */
	private IPv4Address mEndpoint;
	private int mQueueLength;
	private int mSocket;

	/*
	 * Default constructor
	 */
	public void Constructor() {
		mQueueLength = DEFAULT_QUEUE_LENGTH;

		Init();
	}

	/*
	 * 
	 */
	public void Constructor(int port) {
		mEndpoint = new IPv4Address(INADDR_ANY, port);

		Constructor(mEndpoint, DEFAULT_QUEUE_LENGTH);
	}

	/*
	 *
	 */
	public void Constructor(int port, int queueLength) {
		mEndpoint = new IPv4Address(INADDR_ANY, port);
		mQueueLength = queueLength;

		Constructor(mEndpoint, mQueueLength);
	}

	/*
	 *
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
	public int Accept() throws {
		return accept(mSocket);
	}

	/*
	 * Binds the ServerSocket to the address given during object construction
	 */
	public int Bind() modify throws {
		if ( !mEndpoint ) {
			throw new Exception("endpoint not set");
		}

		return bind(mSocket, ISocketAddress mEndpoint);
	}

	/*
	 * Binds the ServerSocket to a given address
	 */
	public int Bind(IPv4Address endpoint) modify throws {
		if ( !endpoint ) {
			throw new Exception("endpoint not set");
		}

		mEndpoint = endpoint;

		return Bind();
	}

	/*
	 * Closes this socket
	 */
	public int Close() throws {
	    return close(mSocket);
	}

	/*
	 * Returns the port on which the socket is listening
	 */
	public int getLocalPort() const {
		if ( !mEndpoint ) {
			return 0;
		}

		return mEndpoint._sa_port;
	}

	private void Init() modify {
	    mSocket = socket(AF_INET, SOCK_STREAM, 0);
	}

	public int Listen() modify {
	    return listen(mSocket, mQueueLength);
	}

	public int ReadInt() {
		return readi(mSocket);
	}

	public string ReadString(int length = -1) {
	    return reads(mSocket, length);
	}
}


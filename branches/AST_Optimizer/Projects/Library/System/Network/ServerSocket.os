
import System.Exception;
import System.Network.Socket;

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

		init();
	}

	/*
	 * Destructor
	 */
	public void Destructor() {
		close();
	}

	/*
	 * Listens for a connection to be made to this socket and accepts it.
	 * The method blocks until a connection is made.
	 */
	public int accept() throws {
		return -1;
	}

	/*
	 * Binds the ServerSocket to the address given during object construction
	 */
	public int bind() modify throws {
	    if ( !mEndpoint ) {
	        throw new Exception("endpoint not set");
	    }

	    return accept(mSocket, ISocketAddress mEndpoint);
	}

	/*
	 * Binds the ServerSocket to a given address
	 */
	public int bind(IPv4Address endpoint) modify throws {
	    if ( !endpoint ) {
	        throw new Exception("endpoint not set");
	    }

	    mEndpoint = endpoint;

	    return accept(mSocket, ISocketAddress mEndpoint);
	}

	/*
	 * Closes this socket
	 */
	public int close() throws {
	    return -1;
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

	private void init() modify {
	    mSocket = socket(AF_INET, SOCK_STREAM, o);
	}

	public int listen() modify {
	    return -1;
	}

	public string readString(int length) {
	    return "";
	}
}



import Socket;

public object ServerSocket {
	/*
	 * Public constants
	 */
	public int DEFAULT_QUEUE_LENGTH const = 50;

	/*
	 * Private members
	 */
	private IPv4Address mAddress;
	private int mQueueLength;

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
		mAddress = new IPv4Address(INADDR_ANY, port);
		mQueueLength = DEFAULT_QUEUE_LENGTH;
	}

	/*
	 *
	 */
	public void Constructor(int port, int queueLength) {
		mAddress = new IPv4Address(INADDR_ANY, port);
		mQueueLength = queueLength;
	}

	/*
	 *
	 */
	public void Constructor(IPv4Address address, int queueLength) {
		mAddress = address;
		mQueueLength = queueLength;
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
	public Socket accept() throws {
		return Socket null;
	}

	/*
	 * Binds the ServerSocket to the address given during object construction
	 */
	public void bind() modify throws {
	}

	/*
	 * Binds the ServerSocket to a given address
	 */
	public void bind(ISocketAddress endpoint) modify throws {
	}

	/*
	 * Closes this socket
	 */
	public void close() throws {
	}

	/*
	 * Returns the port on which the socket is listening
	 */
	public int getLocalPort() const {
		if ( !mAddress ) {
			return 0;
		}

		return mAddress._sa_port;
	}
}


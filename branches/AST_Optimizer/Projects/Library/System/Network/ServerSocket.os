
import Socket;

public object ServerSocket {
	/*
	 * Public constants
	 */
	public int DEFAULT_QUEUE_LENGTH const = 50;

	/*
	 * Private members
	 */
	private ISocketAddress mAddress;
	private int mPort;
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
		mPort = port;
		mQueueLength = DEFAULT_QUEUE_LENGTH;
	}

	/*
	 *
	 */
	public void Constructor(int port, int queueLength) {
		mPort = port;
		mQueueLength = queueLength;
	}

	/*
	 *
	 */
	public void Constructor(int port, int queueLength, ISocketAddress address) {
		mAddress = address;
		mPort = port;
		mQueueLength = queueLength;
	}

	/*
	 * Destructor
	 */
	public void Destructor() {
		close();
	}

	Socket accept() throws {
		return Socket null;
	}

	public void close() throws {
	}
}


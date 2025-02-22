
import System.Collections.Map;
import Message;


public interface IIPCReceiver
{
	public IPCMessage receive( bool waitForMessage = false ) modify;
}


public interface IIPCSender
{
	public void send( int queueID, IPCMessage message ) modify;
	public void send( int queueID, string message ) modify;
}


public object IPCService implements IIPCReceiver, IIPCSender
{
	public void Constructor( int queueID, string processName, bool isOwner = false ) {
		mConnectedQueues = new Map<int, int>();
		mProcessName     = processName;
		mQueueHandle     = msgget( queueID, isOwner );
		mQueueOwner      = isOwner;
	}

	public void Destructor() {
		if ( mQueueOwner ) {
			msgctl( mQueueHandle );
		}
	}

	public IPCService Copy() const {
		var result = new IPCService() {
			result.mConnectedQueues = mConnectedQueues;
			result.mProcessName     = mProcessName;
			result.mQueueHandle     = mQueueHandle;
			result.mQueueOwner      = false;
		}

		return result;
	}

	public bool connect( int queueID ) modify {
		if ( mConnectedQueues.contains( queueID ) ) {
			mConnectedQueues.remove( queueID );
		}

		mConnectedQueues.insert( queueID, msgget( queueID ) );

		return mConnectedQueues[ queueID ] != -1;
	}

	public IPCMessage receive( bool waitForMessage = false ) modify {
		var msg = msgrcv( mQueueHandle, waitForMessage );
		if ( msg ) {
			return new IPCMessage( "", "", msg );
		}

		return IPCMessage null;
	}

	public bool send( int queueID, IPCMessage message ) modify {
		var msg = cast<string>( message );

		return msgsnd( queueID, msg ) != -1;
	}

	public bool send( int queueID, string message ) modify {
		return send( queueID, new IPCMessage( mProcessName, "", message ) );
	}

	private Map<int, int> mConnectedQueues;
	private string mProcessName;
	private int mQueueHandle;
	private bool mQueueOwner;
}

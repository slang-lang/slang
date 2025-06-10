
// library imports
import libLog.Logger;
import libLog.StdOutLogger;
import libParam;

// project imports
import IPCService;


// Constants
public string PROMPT const = "> ";


private object Application
{
	public void Constructor( ILogger logger ) {
		Logger = logger;
	}

	public void Destructor() {
		// nothing to do here
	}

	public void Start( int argc, string args ) modify throws {
		{	// process parameters
			var params = new ParameterHandler( argc, args );

			if ( params.size() != 2 ) {
				throw "Invalid number of parameters, expected 2 received " + params.size();
			}

			QueueID   = cast<int>( params[ "id" ].Value );
			QueueName = params[ "name" ].Value;
		}

		Logger.info( "Opening message queues..." );

		Run();

		Logger.info( "Closing message queues..." );
	}

	private void Read( bool wait ) modify {
		print( Queue.receive( wait ) );
	}

	private void Run() modify {
		Queue = new IPCService( QueueID, QueueName, true );

		IPCMessage msg;
		while ( true ) {
			write( PROMPT );

			var command = cin();

			switch ( command ) {
				case "help": { break; }
				case "read": { Read( false ); break; }
				case "readwait": { Read( true ); break; }
				case "quit": { return; }
				default: { print( "Unknown command '" + command + "'" ); break; }
			}
		}
	}
	
	private ILogger Logger;
	private IPCService Queue;
	private int QueueID;
	private string QueueName;
}

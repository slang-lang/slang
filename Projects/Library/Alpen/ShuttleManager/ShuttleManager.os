
// library imports
import libLog.Logger;

// project imports
import libs.Consts;
import libs.IPCService;
import libs.Job;
import libs.Order;
import libs.Shuttle;
import libs.Storage;


private string SHUTTLE_QUERY const = "SELECT shuttle_id FROM shuttles ORDER BY shuttle_id ASC";


public object ShuttleManager {
	public void Constructor(ILogger logger) {
		mLogger = new Logger(logger, "ShuttleManager");
		mShuttles = new List<Shuttle>();
		mStorage = new Storage(logger);

		mLogger.info("Constructor()");
	}

	public void Destructor() {
		mLogger.info("Destructor()");
	}

	public void process() modify {
		loadShuttles();

		dispatchJobs();
	}

	private void dispatchJobs() modify {
		mLogger.info("Dispatching new jobs...");

		
	}

	private void loadShuttles() modify throws {
		mShuttles.clear();

		int result = DB.Query( SHUTTLE_QUERY );
		if ( !result ) {
			throw DB.Error();
		}

		while( mysql_next_row(result) ) {
			mShuttles.push_back( mStorage.LoadShuttleByID( int mysql_get_field_value(result, "shuttle_id") ) );

			mLogger.info( cast<string>( mShuttles.last() ) );
		}
	}

	private Logger mLogger;
	private List<Shuttle> mShuttles;
	private Storage mStorage;
}


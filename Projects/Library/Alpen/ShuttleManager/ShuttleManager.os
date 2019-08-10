
// library imports
import libLog.Logger;

// project imports
import libs.Consts;
import libs.IPCService;
import libs.Job;
import libs.Order;
import libs.PathFinder;
import libs.Shuttle;
import libs.Storage;


public object ShuttleManager {
	public void Constructor(ILogger logger, IPCService ipcService) {
		mIPCService = ipcService;
		mLogger = new Logger(logger, "ShuttleManager");
		mPathFinder = new PathFinder(logger);
		mShuttles = new List<Shuttle>();
		mStorage = new Storage(logger);

		mLogger.info("Constructor()");
	}

	public void Destructor() {
		mLogger.info("Destructor()");
	}

	public void process() modify {
		mLogger.info("Start processing...");

		bool finishedAJob = true;
		while ( finishedAJob ) {
			loadShuttles();

			dispatchJobs();

			finishedAJob = processJobs();
		}

		mLogger.info("Done processing...");
	}

	private void dispatchJobs() modify {
		mLogger.info("Start dispatching jobs...");

		foreach ( Shuttle shuttle : mShuttles ) {
			if ( shuttle.orders.empty() ) {
				if ( shuttle.stateID == ShuttleState.OCCUPIED ) {
					// reset shuttle state since it has clearly been forgotten
					shuttle.stateID = ShuttleState.READY;
					mStorage.Update(shuttle);
				}

				// this shuttle has no assigned orders
				continue;
			}

			var order = shuttle.orders.first();
			if ( order ) {
				if ( order.stateID >= OrderState.Started && !order.canProceed() ) {
					// order has already been handled => ignore it
					continue;
				}

				if ( order.jobs.empty() ) {
					if ( order.stateID < OrderState.Done ) {
						order.stateID = OrderState.Done;
						mStorage.Update(order);
					}

					// this order has no jobs!?
					continue;
				}

				if ( !executeJob(shuttle, order.jobs.first()) ) {
					mLogger.warning("Could not start " + cast<string>(order) + "!");
					continue;
				}

				order.stateID = OrderState.Started;
				mStorage.Update(order);
			}
		}

		mLogger.info("Finished dispatching jobs...");
	}

	private bool executeJob(Shuttle shuttle, Job job) modify throws {
		if ( !job ) {
			throw "invalid job provided!";
		}

		mLogger.info("executeJob(" + cast<string>(shuttle) + ", " + cast<string>(job) + ")");

		var path = mPathFinder.findPathForShuttle(shuttle, job.position);
		if ( !path ) {
			mLogger.warning("No path found for " + cast<string>(shuttle) + " to " + cast<string>(job.position) + "!");
			return false;
		}

		job.shuttleID = shuttle.shuttleID;
		job.stateID = JobState.Started;
		// For testing only - begin
		job.startTime = time();
		job.endTime = job.startTime + JOB_DURATION + ((shuttle.position == job.position) ? 0 : MOVE_DURATION);
		// For testing only - end
		mStorage.Update(job);

		notifyShuttleAdapter(MSG_WORK_RECEIVED);

		return true;
	}

	private void loadShuttles() modify throws {
		mShuttles.clear();

		int result = DB.Query( SHUTTLE_QUERY );
		while( mysql_next_row(result) ) {
			mShuttles.push_back( mStorage.LoadShuttleByID( int mysql_get_field_value(result, "shuttle_id") ) );

			mLogger.info( cast<string>( mShuttles.last() ) );
		}
	}

	private void notifyShuttleAdapter(string message) modify {
		mIPCService.send(SHUTTLEADAPTER_QUEUE, message);
	}

	private bool processJobs() modify {
		mLogger.info("Start processing jobs...");

		bool finishedAJob = false;

		foreach ( Shuttle shuttle : mShuttles ) {
			if ( shuttle.orders.empty() ) {
				continue;
			}

			var order = shuttle.orders.first();
			if ( order ) {
				if ( !order.jobs.empty() ) {
					var job = order.jobs.first();
					if ( time() > job.endTime ) {
						mLogger.info(cast<string>(job) + " is done.");

						shuttle.position = job.position;
						mStorage.Update(shuttle);

						job.stateID = JobState.Done;
						mStorage.Update(job);

						finishedAJob = true;
					}
				}

				if ( !order.hasOpenJobs() ) {
					mLogger.info(cast<string>(order) + " is done.");

					order.stateID = OrderState.Done;
					mStorage.Update(order);

					shuttle.stateID = ShuttleState.READY;
					mStorage.Update(shuttle);
				}
			}
		}

		mLogger.info("Finished processing jobs...");

		return finishedAJob;
	}

	private IPCService mIPCService;
	private Logger mLogger;
	private PathFinder mPathFinder;
	private List<Shuttle> mShuttles;
	private Storage mStorage;
}


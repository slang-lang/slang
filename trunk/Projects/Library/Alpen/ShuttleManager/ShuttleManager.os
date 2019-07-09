
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


private string SHUTTLE_QUERY const = "SELECT shuttle_id FROM shuttles ORDER BY shuttle_id ASC";


public object ShuttleManager {
	public void Constructor(ILogger logger) {
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
					// reset shuttle state since it has clearly been forgotten;
					shuttle.stateID = ShuttleState.READY;
					store(shuttle);
				}

				continue;
			}

			var order = shuttle.orders.first();
			if ( order ) {
				if ( order.stateID >= OrderState.Started && !order.canProceed() ) {
					// order has already been handled => ignore it
					continue;
				}

				if ( !executeJob(shuttle, order.jobs.first()) ) {
					mLogger.warning("Could not start " + cast<string>(order) + "!");
					continue;
				}

				order.stateID = OrderState.Started;
				store(order);
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
		job.startTime = time();
		job.stateID = JobState.Started;
		store(job);

		return true;
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
					if ( time() - job.startTime > JOB_DURATION ) {
						mLogger.info(cast<string>(job) + " is done.");

						shuttle.position = job.position;
						store(shuttle);

						job.stateID = JobState.Done;
						store(job);

						finishedAJob = true;
					}
				}

				if ( !order.hasOpenJobs() ) {
					mLogger.info(cast<string>(order) + " is done.");

					order.stateID = OrderState.Done;
					store(order);

					shuttle.stateID = ShuttleState.READY;
					store(shuttle);
				}
			}
		}

		mLogger.info("Finished processing jobs...");

		return finishedAJob;
	}

    private void store(Job job) modify {
        string query = "UPDATE jobs SET" +
						" shuttle_id = " + job.shuttleID +
						", job_state_id = " + cast<string>( job.stateID ) +
						", start_time = " + job.startTime +
						" WHERE job_id = " + job.jobID;
        mLogger.debug(query);

        DB.Execute(query);
    }

    private void store(Order order) modify {
        string query = "UPDATE orders SET" +
						" shuttle_id = " + order.shuttleID +
						", order_state_id = " + cast<string>( order.stateID ) +
						" WHERE order_id = " + order.orderID;
        mLogger.debug(query);

        DB.Execute(query);
    }

    private void store(Shuttle shuttle) modify {
        string query = "UPDATE shuttles SET" +
						" level_id = " + cast<string>(shuttle.position.levelID) +
						", position_id = " + cast<string>(shuttle.position.positionID) +
						", shuttle_mode_id = " + cast<string>(shuttle.modeID) +
						", shuttle_state_id = " + cast<string>( shuttle.stateID ) +
						" WHERE shuttle_id = " + shuttle.shuttleID;
        mLogger.debug(query);

        DB.Execute(query);
    }

	private Logger mLogger;
	private PathFinder mPathFinder;
	private List<Shuttle> mShuttles;
	private Storage mStorage;
}


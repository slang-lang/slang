
// library imports

// project imports
import Database;
import Job;
import Order;
import Shuttle;


private string QUERY_JOB_FULL const = "SELECT * FROM jobs WHERE job_id = ";
private string QUERY_ORDER_FULL const = "SELECT o.*, j.* FROM orders o LEFT JOIN jobs j ON (j.order_id = o.order_id AND j.job_state_id < 3) WHERE o.order_id = ";
private string QUERY_SHUTTLE_FULL const = "SELECT s.*, o.*, j.* FROM shuttles s LEFT JOIN orders o ON (o.shuttle_id = s.shuttle_id AND o.order_state_id < 4) LEFT JOIN jobs j ON (j.order_id = o.order_id AND j.job_state_id < 3) WHERE s.shuttle_id = ";
private string QUERY_SHUTTLE_LIGHT const = "SELECT s.*, o.order_id FROM shuttles s LEFT JOIN orders o ON (o.shuttle_id = s.shuttle_id AND o.order_state_id < 4) WHERE s.shuttle_id = ";

public object Storage {
    public void Constructor(ILogger logger) {
        mLogger = new Logger(logger, "Storage");
    }

    public Job LoadJobByID(int jobID) modify throws {
        //mLogger.debug("LoadJobByID(" + jobID + ")");

        int result = DB.Query( QUERY_JOB_FULL + jobID );
        if ( !result ) {
            throw DB.Error();
        }

        Job job;

        if ( mysql_next_row(result) ) {
            job = LoadJobByResult(result);
        }

        mLogger.debug( cast<string>( job ));
        return job;
    }

    public Job LoadJobByResult(int result) const {
        Job job = new Job();
        job.jobID = int mysql_get_field_value(result, "job_id");
        job.jobTypeID = JobType cast<int>( mysql_get_field_value(result, "job_type_id") );
        job.orderID = int mysql_get_field_value(result, "order_id");
        job.position.levelID = int mysql_get_field_value(result, "level_id");
        job.position.positionID = int mysql_get_field_value(result, "position_id");
        job.sequence = int mysql_get_field_value(result, "sequence");
        job.shuttleID = int mysql_get_field_value(result, "shuttle_id");
        job.stateID = JobState cast<int>( mysql_get_field_value(result, "job_state_id") );

        job.endTime = int mysql_get_field_value(result, "end_time");
        job.startTime = int mysql_get_field_value(result, "start_time");

        return job;
    }

    public Order LoadOrderByID(int orderID) modify throws {
        //mLogger.debug("LoadOrderByID(" + orderID + ")");

        int result = DB.Query( QUERY_ORDER_FULL + orderID );
        if ( !result ) {
            throw DB.Error();
        }

        Order order;

        while ( mysql_next_row(result) ) {
            if ( !order ) {
                order = LoadOrderByResult(result);
            }
            int jobID = mysql_get_field_value(result, "job_id");
            if ( jobID ) {
                //order.jobs.push_back( LoadJobByID( jobID ) );
                order.jobs.push_back( LoadJobByResult( result ) );
            }
        }

        mLogger.debug( cast<string>( order ));
        return order;
    }

    public Order LoadOrderByResult(int result) const {
        Order order = new Order();
        order.orderID = int mysql_get_field_value(result, "order_id");
        order.orderTypeID = OrderType cast<int>( mysql_get_field_value(result, "order_type_id") );
        order.priority = int mysql_get_field_value(result, "priority");
        order.sequence = int mysql_get_field_value(result, "sequence");
        order.shuttleID = int mysql_get_field_value(result, "shuttle_id");
        order.stateID = OrderState cast<int>( mysql_get_field_value(result, "order_state_id") );
        return order;
    }

    public Shuttle LoadShuttleByID(int shuttleID) modify throws {
        //mLogger.debug("LoadShuttleByID(" + shuttleID + ")");

        int result = DB.Query( QUERY_SHUTTLE_LIGHT + shuttleID );
        if ( !result ) {
            throw DB.Error();
        }

        Shuttle shuttle;

        while ( mysql_next_row(result) ) {
            if ( !shuttle ) {
                shuttle = LoadShuttleByResult(result);
            }

            int orderID = int mysql_get_field_value(result, "order_id");
            if ( orderID ) {
                shuttle.orders.push_back( LoadOrderByID( orderID ) );
                shuttle.countAssignedOrders = shuttle.orders.size();
            }
        }

        //mLogger.debug( cast<string>( shuttle ));
        return shuttle;
    }

    public Shuttle LoadShuttleByResult(int result) const {
        Shuttle shuttle = new Shuttle();
        shuttle.batteryLevelID = ShuttleBatteryLevel cast<int>( mysql_get_field_value(result, "shuttle_battery_level_id") );
        //shuttle.containerLimit = int mysql_get_field_value(result, "container_limit");
        shuttle.position.levelID = int mysql_get_field_value(result, "level_id");
        shuttle.modeID = ShuttleMode cast<int>( mysql_get_field_value(result, "shuttle_mode_id") );
        shuttle.position.positionID = int mysql_get_field_value(result, "position_id");
        shuttle.stateID = ShuttleState cast<int>( mysql_get_field_value(result, "shuttle_state_id") );
        shuttle.shuttleID = int mysql_get_field_value(result, "shuttle_id");
        shuttle.shuttleTypeID = ShuttleType cast<int>( mysql_get_field_value(result, "shuttle_id") );
        return shuttle;
    }

    private Logger mLogger;
}
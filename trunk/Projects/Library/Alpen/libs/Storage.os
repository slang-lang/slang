
// library imports

// project imports
import Database;
import Job;
import Order;
import Shuttle;


private string QUERY_JOB_FULL const = "SELECT * FROM jobs WHERE job_id = ";
private string QUERY_ORDER_FULL const = "SELECT o.*, j.* FROM orders o LEFT JOIN jobs j ON (j.order_id = o.order_id) WHERE o.order_id = ";
private string QUERY_SHUTTLE_FULL const = "SELECT s.*, o.*, j.* FROM shuttles s LEFT JOIN orders o ON (o.shuttle_id = s.shuttle_id) LEFT JOIN jobs j ON (j.order_id = o.order_id) WHERE s.shuttle_id = ";
private string QUERY_SHUTTLE_LIGHT const = "SELECT s.*, o.order_id FROM shuttles s LEFT JOIN orders o ON (o.shuttle_id = s.shuttle_id) WHERE s.shuttle_id = ";

public object Storage {
    public void Constructor(ILogger logger) {
        mLogger = new Logger(logger, "Storage");
    }

    public Job LoadJobByID(int jobID) modify throws {
        int result = DB.Query( QUERY_JOB_FULL + jobID );
        if ( !result ) {
            throw DB.Error();
        }

        Job job;

        if ( mysql_next_row(result) ) {
            job = LoadJobByResult(result);
        }

        //mLogger.debug( cast<string>( job ));
        return job;
    }

    public Job LoadJobByResult(int result) const {
        Job job = new Job();
        job.jobID = int mysql_get_field_value(result, "job_id");
        job.jobTypeID = JobType cast<int>( mysql_get_field_value(result, "job_type_id") );
        job.levelID = int mysql_get_field_value(result, "level_id");
        job.orderID = int mysql_get_field_value(result, "order_id");
        job.positionID = int mysql_get_field_value(result, "position_id");
        job.sequence = int mysql_get_field_value(result, "sequence");
        job.stateID = JobState cast<int>( mysql_get_field_value(result, "job_state_id") );
        return job;
    }

    public Order LoadOrderByID(int orderID) modify throws {
        int result = DB.Query( QUERY_ORDER_FULL + orderID );
        if ( !result ) {
            throw DB.Error();
        }

        Order order;

        while ( mysql_next_row(result) ) {
            if ( !order ) {
                order = LoadOrderByResult(result);
            }

            order.jobs.push_back( LoadJobByResult(result) );
        }

        //mLogger.debug( cast<string>( order ));
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
        shuttle.levelID = int mysql_get_field_value(result, "level_id");
        shuttle.modeID = ShuttleMode cast<int>( mysql_get_field_value(result, "shuttle_mode_id") );
        shuttle.positionID = int mysql_get_field_value(result, "position_id");
        shuttle.stateID = ShuttleState cast<int>( mysql_get_field_value(result, "shuttle_id") );
        shuttle.shuttleTypeID = ShuttleType cast<int>( mysql_get_field_value(result, "shuttle_id") );
        shuttle.shuttleID = int mysql_get_field_value(result, "shuttle_id");
        return shuttle;
    }

    private Logger mLogger;
}

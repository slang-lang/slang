
// library imports

// project imports
import Order;


public interface IShuttleSortAlgorithm {
    public bool compare(Shuttle left const, Shuttle right const) const;
}

public enum ShuttleBatteryLevel {
    UNKNOWN = 0,
    CRITICAL,
    LOW,
    NORMAL,
    FULL;
}

public enum ShuttleMode {
    OUTOFORDER = 0,
    MANUAL,
    AUTOMATIC;
}

public enum ShuttleState {
    SUSPENDED = 0,
    READY,
    OCCUPIED;
}

public enum ShuttleType {
    AlpenShuttle = 0,
    OpenShuttle;
}

public object Shuttle {
    public ShuttleBatteryLevel batteryLevelID;
    public int containerLimit;
    public int countAssignedOrders;
    public int levelID;
    public ShuttleMode modeID;
    public int positionID;
    public int shuttleID;
    public IShuttleSortAlgorithm sortAlgorithm;
    public ShuttleState stateID;
    public ShuttleType shuttleTypeID;

    public void Constructor() {
        // nothing to do here
    }

    public void Constructor(int dbresult) {
        load(dbresult);
    }

    public bool canAcceptOrder(Order order) const {
        //print( "" + cast<string>( this ) + ": " + cast<string>( order ) );

        return countAssignedOrders < containerLimit;
    }

    public bool operator==(Shuttle other const) const {
        return shuttleID == other.shuttleID;
    }

    public bool operator<(Shuttle other const) const {
        if ( sortAlgorithm ) {
            return sortAlgorithm.compare(this, other);
        }

        // fallback if no sort algorithm is set, this should never be used
        return false;
    }

    public string =operator(string) const {
        return "{ shuttleID: " + shuttleID +
               ", shuttleTypeID: " + cast<string>( shuttleTypeID ) +
               ", modeID: " + cast<string>( modeID ) +
               ", stateID: " + cast<string>( stateID ) +
               ", batteryLevelID: " + cast<string>( batteryLevelID ) +
               ", levelID: " + levelID +
               ", positionID: " + positionID +
               ", containerLimit: " + containerLimit +
               "}";
    }

    private void load(int dbresult) modify {
        batteryLevelID = ShuttleBatteryLevel cast<int>( mysql_get_field_value(dbresult, "shuttle_battery_level_id") );
        containerLimit = cast<int>( mysql_get_field_value(dbresult, "container_limit") );
        //countAssignedOrders = cast<int>( mysql_get_field_value(dbresult, "count_assigned_orders") );
        levelID = cast<int>( mysql_get_field_value(dbresult, "level_id") );
        modeID = ShuttleMode cast<int>( mysql_get_field_value(dbresult, "shuttle_mode_id") );
        positionID = cast<int>( mysql_get_field_value(dbresult, "position_id") );
        shuttleID = cast<int>( mysql_get_field_value(dbresult, "shuttle_id") );
        stateID = ShuttleState cast<int>( mysql_get_field_value(dbresult, "shuttle_state_id") );
        shuttleTypeID = ShuttleType cast<int>( mysql_get_field_value(dbresult, "shuttle_type_id") );
    }
}

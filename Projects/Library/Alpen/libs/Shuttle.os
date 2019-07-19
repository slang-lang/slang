
// library imports
import System.Collections.List;

// project imports
import Order;
import Path;
import Position;


public interface IShuttleSortAlgorithm {
    public bool compare(Shuttle left const, Shuttle right const) const;
}

public object ShuttleID {
    public int ID const;

    public void Constructor(int id) {
        ID = id;
    }

    public string =operator(string) const {
        return "ShuttleID{" + ID + "}";
    }
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
    public List<Order> orders;
    public Path path;
    public Position position;
    public int shuttleID;
    public IShuttleSortAlgorithm sortAlgorithm;
    public ShuttleState stateID;
    public ShuttleType shuttleTypeID;

    public void Constructor() {
        orders = new List<Order>();
        position = new Position();
    }

    public void Constructor(int dbresult) {
        orders = new List<Order>();
        position = new Position();

        load(dbresult);
    }

    public bool canAcceptOrder(Order order) const {
        //print( "" + cast<string>( this ) + ": " + cast<string>( order ) );

        return countAssignedOrders < containerLimit;
    }

    public bool hasWork() const {
        return orders.size() > 0;
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
        return "Shuttle { shuttleID: " + shuttleID +
               ", shuttleTypeID: " + cast<string>( shuttleTypeID ) +
               ", modeID: " + cast<string>( modeID ) +
               ", stateID: " + cast<string>( stateID ) +
               ", batteryLevelID: " + cast<string>( batteryLevelID ) +
               ", position: " + cast<string>(position) +
               ", containerLimit: " + containerLimit +
               ", countAssignedOrders: " + countAssignedOrders +
               "}";
    }

    private void load(int dbresult) modify {
        batteryLevelID = ShuttleBatteryLevel cast<int>( mysql_get_field_value(dbresult, "shuttle_battery_level_id") );
        containerLimit = cast<int>( mysql_get_field_value(dbresult, "container_limit") );
        //countAssignedOrders = cast<int>( mysql_get_field_value(dbresult, "count_assigned_orders") );
        //levelID = cast<int>( mysql_get_field_value(dbresult, "level_id") );
        modeID = ShuttleMode cast<int>( mysql_get_field_value(dbresult, "shuttle_mode_id") );
        //positionID = mysql_get_field_value(dbresult, "position_id");
        shuttleID = cast<int>( mysql_get_field_value(dbresult, "shuttle_id") );
        stateID = ShuttleState cast<int>( mysql_get_field_value(dbresult, "shuttle_state_id") );
        shuttleTypeID = ShuttleType cast<int>( mysql_get_field_value(dbresult, "shuttle_type_id") );

        position = new Position(
            cast<int>( mysql_get_field_value(dbresult, "level_id") ),
            cast<int>( mysql_get_field_value(dbresult, "position_id") )
        );
    }
}

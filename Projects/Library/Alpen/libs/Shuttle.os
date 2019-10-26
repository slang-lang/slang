
// library imports
import System.Collections.List;

// project imports
import Graph.Path;
import Order;
import Position;


public enum ShuttleBatteryLevel {
    UNKNOWN = 0,
    CRITICAL,
    LOW,
    NORMAL,
    HIGH;
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
    public ShuttleType typeID;

    public void Constructor() {
        orders = new List<Order>();
        position = new Position();
    }

    public void Constructor(int dbResult) {
        Constructor();

        load(dbResult);
    }

    public bool canAcceptOrder(Order order const) const {
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
               ", typeID: " + cast<string>( typeID ) +
               ", modeID: " + cast<string>( modeID ) +
               ", stateID: " + cast<string>( stateID ) +
               ", batteryLevelID: " + cast<string>( batteryLevelID ) +
               ", position: " + cast<string>( position ) +
               ", containerLimit: " + containerLimit +
               ", countAssignedOrders: " + countAssignedOrders +
               "}";
    }

    private void load(int dbResult) modify {
        batteryLevelID = ShuttleBatteryLevel cast<int>( mysql_get_field_value(dbResult, "shuttle_battery_level_id") );
        containerLimit = cast<int>( mysql_get_field_value(dbResult, "container_limit") );
        //countAssignedOrders = cast<int>( mysql_get_field_value(dbResult, "count_assigned_orders") );
        modeID = ShuttleMode cast<int>( mysql_get_field_value(dbResult, "shuttle_mode_id") );
        position = new Position(
            cast<int>( mysql_get_field_value(dbResult, "level_id") ),
            cast<int>( mysql_get_field_value(dbResult, "position_id") )
        );
        shuttleID = cast<int>( mysql_get_field_value(dbResult, "shuttle_id") );
        stateID = ShuttleState cast<int>( mysql_get_field_value(dbResult, "shuttle_state_id") );
        typeID = ShuttleType cast<int>( mysql_get_field_value(dbResult, "shuttle_type_id") );
    }
}


// library imports
import System.Collections.Set;

// project imports
import IDispatchStep;


// Pre condition: none
// Post condition: returns a list of shuttles that is sorted by battery level (from high to low)

private object SortByBatteryLevel implements IShuttleSortAlgorithm {
    public bool compare(Shuttle left const, Shuttle right const) const {
        //print(cast<string>(left) + " vs " + cast<string>(right));

        return left.batteryLevelID < right.batteryLevelID;
    }
}

public object SortShuttlesByBatteryLevel extends SortingStep implements IDispatchStep {
    public DispatchData dispatch(DispatchData data const) modify {
        // sort shuttles by battery level
        var sortByBattery = cast<IShuttleSortAlgorithm>( new SortByBatteryLevel() );

        var shuttleSet = new Set<Shuttle>();
        foreach ( Shuttle shuttle : data.shuttles ) {
            shuttle.sortAlgorithm = sortByBattery;

            shuttleSet.insert(shuttle);
        }

        var usableShuttles = new List<Shuttle>();
        foreach ( Shuttle shuttle : shuttleSet ) {
            usableShuttles.push_back(shuttle);
        }

        return new DispatchData(cast<Object>(data.orders), cast<Object>(usableShuttles));
    }

    public string getName() const {
        return "SortShuttlesByBatteryLevel";
    }
}
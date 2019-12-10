
// library imports
import System.Collections.Set;

// project imports
import IDispatchStep;


// Pre condition: none
// Post condition: returns a list of shuttles that is sorted by state (occupied shuttles are preferred)

private object SortByOccupacity implements IShuttleSortAlgorithm {
    public bool compare(Shuttle left const, Shuttle right const) const {
        print(cast<string>(left) + " vs " + cast<string>(right));

        return left.stateID == ShuttleState.READY && left.stateID > right.stateID;
    }
}

public object PreferUnoccupiedShuttles extends SortingStep implements IDispatchStep {
    public DispatchData dispatch(DispatchData data const) modify {
        // sort shuttles by occupacity
        var sortByOccupacity = cast<IShuttleSortAlgorithm>( new SortByOccupacity() );

        var shuttleSet = new Set<Shuttle>();
        foreach ( Shuttle shuttle : data.shuttles ) {
            shuttle.sortAlgorithm = sortByOccupacity;

            shuttleSet.insert(shuttle);
        }

        var usableShuttles = new List<Shuttle>();
        foreach ( Shuttle shuttle : shuttleSet ) {
            usableShuttles.push_back(shuttle);
        }

        return new DispatchData(cast<Object>(data.orders), cast<Object>(usableShuttles));
    }

    public string getName() const {
        return typeid(this);
    }
}

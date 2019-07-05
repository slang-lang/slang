
// library imports

// project imports
import IDispatchStep;


// Pre condition: none
// Post condition: returns a list of shuttles that is sorted by distance to the _first_ order (from near to far)

public object SortByDistance implements IShuttleSortAlgorithm {
    public void Constructor(Order _order const) {
        order = _order;
    }

    public bool compare(Shuttle left const, Shuttle right const) const {
        print(cast<string>(left) + " vs " + cast<string>(right));

        return left.positionID * left.positionID * order.orderID < right.positionID * right.positionID * order.orderID;
    }

    private Order order const;
}

public object SortShuttlesByDistance extends SortingStep implements IDispatchStep {
    public DispatchData dispatch(DispatchData data const) modify {
        // sort shuttles by distance to first order
        var order = data.orders.first();
        var sortByDistance = cast<IShuttleSortAlgorithm>( new SortByDistance(order) );
        var shuttles = new Set<Shuttle>();

        foreach ( Shuttle shuttle : data.shuttles ) {
            // do some fake calculations
            shuttle.sortAlgorithm = sortByDistance;

            shuttles.insert(shuttle);
        }

        var sortedShuttles = new List<Shuttle>();
        foreach ( Shuttle shuttle : shuttles ) {
            sortedShuttles.push_back(shuttle);
        }

        return new DispatchData(cast<Object>(data.orders), cast<Object>(sortedShuttles));
    }

    public string getName() const {
        return "SortShuttlesByDistance";
    }
}

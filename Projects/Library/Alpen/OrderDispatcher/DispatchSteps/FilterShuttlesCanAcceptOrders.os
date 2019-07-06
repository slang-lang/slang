
// library imports

// project imports
import IDispatchStep;


// Pre condition: none
// Post condition: only shuttles which can receive new orders will be returned

public object FilterShuttlesCanAcceptOrders extends FilteringStep implements IDispatchStep {
    public DispatchData dispatch(DispatchData data const) modify {
        // collect a list of all shuttles that are allowed to receive new orders
        var acceptableOrders = new List<Order>();

        foreach ( Shuttle shuttle : data.shuttles ) {
            foreach ( Order order : data.orders ) {
                if ( shuttle.stateID == ShuttleState.READY && !acceptableOrders.contains(order) ) {
                    acceptableOrders.push_back(order);
                }
            }
        }

        return new DispatchData(cast<Object>(acceptableOrders), cast<Object>(data.shuttles));
    }

    public string getName() const {
        return "FilterShuttlesCanAcceptOrders";
    }
}
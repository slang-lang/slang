
// library imports

// project imports
import IDispatchStep;


// Pre condition: none
// Post condition: only shuttles which can receive new orders will be returned

public object FilterShuttlesByBatteryLevel extends FilteringStep implements IDispatchStep {
    public DispatchData dispatch(DispatchData data const) modify {
        // collect a list of all shuttles that are allowed to receive new orders
        var dispatchableShuttles = new List<Shuttle>();

        foreach ( Shuttle shuttle : data.shuttles ) {
            if ( shuttle.batteryLevelID > ShuttleBatteryLevel.LOW ) {
                dispatchableShuttles.push_back(shuttle);
            }
        }

        return new DispatchData(data.orders, dispatchableShuttles);
    }

    public string getName() const {
        return "FilterShuttlesCanAcceptOrders";
    }
}
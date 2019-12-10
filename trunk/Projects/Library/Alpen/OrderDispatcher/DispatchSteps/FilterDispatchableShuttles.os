
// library imports

// project imports
import IDispatchStep;


// Pre condition: none
// Post condition: only shuttles which can receive new orders will be returned

public object FilterDispatchableShuttles extends FilteringStep implements IDispatchStep {
    public DispatchData dispatch(DispatchData data const) modify {
        // collect a list of shuttles that are allowed to receive new orders
        var filteredShuttles = new List<Shuttle>();

        foreach ( Shuttle shuttle : data.shuttles ) {
            if ( shuttle.modeID == ShuttleMode.AUTOMATIC && shuttle.stateID >= ShuttleState.READY ) {
                filteredShuttles.push_back(shuttle);
            }
        }

        return new DispatchData(cast<Object>(data.orders), cast<Object>(filteredShuttles));
    }

    public string getName() const {
        return "FilterDispatchableShuttles";
    }
}


// library imports

// project imports
import IDispatchStep;


// Pre condition: expects a list of orders that is sorted by priority
// Post condition: only orders with the highest priority will be returned

public object FilterOrdersByPriority extends FilteringStep implements IDispatchStep {
    public DispatchData dispatch(DispatchData data const) modify {
        // filter orders by highest priority
        var lastPrio = -1;
        var filteredOrders = new List<Order>();

        foreach ( Order order : data.orders ) {
            if ( lastPrio != -1 && lastPrio < order.priority ) {
                // we have collected all orders with the highest priority set
                break;
            }

            lastPrio = order.priority;
            filteredOrders.push_back(order);
        }

        return new DispatchData(cast<Object>(filteredOrders), cast<Object>(data.shuttles));
    }

    public string getName() const {
        return "FilterOrdersByPriority";
    }
}
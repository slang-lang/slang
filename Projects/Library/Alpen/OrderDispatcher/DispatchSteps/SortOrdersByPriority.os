
// library imports
import System.Collections.Set;

// project imports
import IDispatchStep;


// Pre condition: none
// Post condition: returns a list of orders that is sorted by priority

public object SortByPrio implements IOrderSortAlgorithm {
    public bool compare(Order left const, Order right const) const {
        return left.priority < right.priority;
    }
}

public object SortOrdersByPriority extends SortingStep implements IDispatchStep {
    public DispatchData dispatch(DispatchData data const) modify {
        // sort orders by priority
        var sortByPriority = cast<IOrderSortAlgorithm>( new SortByPrio() );

        var orders = new Set<Order>();
        foreach ( Order order : data.orders ) {
            order.sortAlgorithm = sortByPriority;

            orders.insert(order);
        }

        // collect a list of all orders with the highest prio
        var sortedOrders = new List<Order>();
        foreach ( Order order : orders ) {
            sortedOrders.push_back(order);
        }

        return new DispatchData(sortedOrders, data.shuttles);
    }

    public string getName() const {
        return "SortOrdersByPriority";
    }
}
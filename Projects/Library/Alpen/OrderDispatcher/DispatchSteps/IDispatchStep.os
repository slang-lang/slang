
// library imports
import System.Collections.List;

// project imports
import libs.Order;
import libs.Shuttle;


public object DispatchData {
    public List<Order> orders const;
    public List<Shuttle> shuttles const;

    public void Constructor(List<Order> _orders const, List<Shuttle> _shuttles const) {
        orders = _orders;
        shuttles = _shuttles;
    }

    public bool isSingleShuttle() const {
        return shuttles && shuttles.size() == 1;
    }

    public bool isAtLeastOneOrder() const {
        return orders && orders.size() >= 1;
    }

    public bool isValid() const {
        return orders && orders.size() && shuttles && shuttles.size();
    }

    public string =operator(string) const {
        return "Orders: " + orders.size() + ", Shuttles: " + shuttles.size();
    }
}

public interface IDispatchStep {
    public DispatchData dispatch(DispatchData data const) modify;
    public string getName() const;
}

/*
 *  object FilteringStep: base type for all filtering dispatch steps
 */
public object FilteringStep;

/*
 *  object SortingStep: base type for all sorting dispatch steps
 */
public object SortingStep;

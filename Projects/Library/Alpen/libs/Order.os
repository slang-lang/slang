
// library imports
import System.Collections.List;

// project imports
import Job;


public enum OrderState {
    New = 1,
    Assigned,
    Started,
    Done,
    Cancelled;
}

public enum OrderType {
    Transport = 1,
    Charge;
}

public interface IOrderSortAlgorithm {
    public bool compare(Order left const, Order right const) const;
}

public object Order {
    public List<Job> jobs;
    public int orderID;
    public OrderType orderTypeID;
    public int priority;
    public int sequence;
    public int shuttleID;
    public IOrderSortAlgorithm sortAlgorithm;
    public OrderState stateID;

    public void Constructor() {
        jobs = new List<Job>();
    }

    public void Constructor(int dbresult) {
        jobs = new List<Job>();

        load(dbresult);
    }

    public bool canProceed() const {
        foreach ( Job job : jobs ) {
            if ( job.stateID < JobState.Started ) {
                return true;
            }

            return false;
        }
    }

    public bool hasOpenJobs() const {
        foreach ( Job job : jobs ) {
            if ( job.stateID < JobState.Done ) {
                return true;
            }
        }

        return false;
    }

    public bool operator==(Order other const) const {
        return orderID == other.orderID;
    }

    public bool operator<(Order other const) const {
        if ( sortAlgorithm ) {
            return sortAlgorithm.compare(this, other);
        }

        // fallback if no sort algorithm is set, this should never be used
        return false;
    }

    public string =operator(string) const {
        return "Order { orderID: " + orderID +
               ", orderTypeID: " + cast<string>( orderTypeID ) +
               ", priority: " + priority +
               ", stateID: " + cast<string>( stateID ) +
               ", sequence: " + sequence +
               ", shuttleID: " + shuttleID +
               "}";
    }

    private void load(int dbresult) modify {
        orderID = cast<int>( mysql_get_field_value(dbresult, "order_id") );
        orderTypeID = OrderType cast<int>( mysql_get_field_value(dbresult, "order_type_id") );
        priority = cast<int>( mysql_get_field_value(dbresult, "priority") );
        sequence = cast<int>( mysql_get_field_value(dbresult, "sequence") );
        shuttleID = cast<int>( mysql_get_field_value(dbresult, "shuttle_id") );
        stateID = OrderState cast<int>( mysql_get_field_value(dbresult, "order_state_id") );
    }
}


// library imports
import System.Collections.List;
import libLog.Logger;

// project imports
import libs.IPC;
import libs.Order;
import libs.Shuttle;
import DispatchSteps.FilterDispatchableShuttles;
import DispatchSteps.FilterOrdersByPriority;
import DispatchSteps.FilterShuttlesCanAcceptOrders;
import DispatchSteps.SortOrdersByPriority;
import DispatchSteps.SortShuttlesByBatteryLevel;
import DispatchSteps.SortShuttlesByDistance;


public object Dispatcher {
    public void Constructor(ILogger logger, int connection) {
        mConnection = connection;
        mDispatchSteps = new List<IDispatchStep>();
        mLogger = logger;
        mOrders = new List<Order>();
        mShuttles = new List<Shuttle>();

        ORDER_QUERY = "SELECT * FROM orders WHERE state = " + string OrderState.New;
        SHUTTLE_QUERY = "SELECT s.*, st.* FROM shuttles s " +
                        "JOIN shuttle_type st ON (st.shuttle_type_id = s.shuttle_type_id) " +
                        "LEFT JOIN orders ord ON (ord.shuttle_id = s.shuttle_id) "; /* +
                        "WHERE s.mode = " + cast<string>( ShuttleMode.Automatic ) + " AND s.state = " + cast<string>( ShuttleState.Ready );
                        */

        init();
    }

    public void dispatch() modify {
        mLogger.info("Dispatching new orders...");

        // loop as long as there are free shuttles and dispatchable orders available
        while ( true ) {
            loadOrders();
            loadShuttles();

            printStats();

            var data = new DispatchData( cast<Object>( mOrders ), cast<Object>( mShuttles) );
            if ( mOrders.empty() || mShuttles.empty() ) {
                mLogger.warning("No dispatchable orders found");
                return;
            }

            // run through all dispatch steps as often valid results are still returned
            foreach ( IDispatchStep step : mDispatchSteps ) {
                mLogger.info("Executing step '" + step.getName() + "' with " + cast<string>( data ));

                var newData = step.dispatch(data);

                if ( !newData.isValid() ) {
                    mLogger.debug("No valid result found");
                    break;
                }

                data = newData;

                mLogger.info("Executed step '" + step.getName() + "' with " + cast<string>( data ));
            }

            if ( !data.isValid() ) {
                mLogger.warning("No dispatchable orders found");
                break;
            }

            var order = data.orders.first();
            var shuttle = data.shuttles.first();

            order.shuttleID = shuttle.shuttleID;
            order.state = OrderState.Assigned;
            store(order);

            shuttle.state = ShuttleState.Active;
            store(shuttle);


            sleep(2000);
        }
    }

    public void loadOrders() modify throws {
        mOrders.clear();

        mLogger.debug("loadOrders(Query: '" + ORDER_QUERY + "')");

        int result = execute(ORDER_QUERY);
        while ( mysql_next_row(result) ) {
            mOrders.push_back( new Order(result) );
        }
    }

    public void loadShuttles() modify throws {
        mShuttles.clear();

        mLogger.debug("loadShuttles(Query: '" + SHUTTLE_QUERY + "')");

        int result = execute(SHUTTLE_QUERY);
        while ( mysql_next_row(result) ) {
            mShuttles.push_back( new Shuttle(result) );
        }
    }

    public void printStats() const {
        int activeShuttles;
        foreach ( Shuttle shuttle : mShuttles ) {
            if ( shuttle.state == ShuttleState.Active ) {
                print( cast<string>( shuttle ) );
                activeShuttles++;
            }
        }

        int newOrders;
        foreach ( Order order : mOrders ) {
            if ( order.state == OrderState.New ) {
                print( cast<string>( order ) );
                newOrders++;
            }
        }

        print("Shuttles: " + mShuttles.size() + " (" + activeShuttles + ")");
        print("Orders: " + mOrders.size() + " (" + newOrders + ")");
    }

    private int execute(string query) const throws {
        int error = mysql_query(mConnection, query);
        if ( error ) {
            throw mysql_error(mConnection);
        }

        try { return mysql_store_result(mConnection); }

        return 0;
    }

    private void init() modify {
        mLogger.info("Initializing...");
        initDispatchSteps();
    }

    private void initDispatchSteps() modify {
        mLogger.info("Initializing dispatch steps...");

        mDispatchSteps.push_back( cast<IDispatchStep>( new FilterDispatchableShuttles() ) );
        mDispatchSteps.push_back( cast<IDispatchStep>( new SortOrdersByPriority() ) );
        mDispatchSteps.push_back( cast<IDispatchStep>( new FilterOrdersByPriority() ) );
        mDispatchSteps.push_back( cast<IDispatchStep>( new FilterShuttlesCanAcceptOrders() ) );
        mDispatchSteps.push_back( cast<IDispatchStep>( new SortShuttlesByBatteryLevel() ) );
        mDispatchSteps.push_back( cast<IDispatchStep>( new SortShuttlesByDistance() ) );
    }

    private void store(Order order) const {
        string query = "UPDATE orders SET sequence = " + order.sequence + ", shuttle_id = " + order.shuttleID + ", state = " + cast<string>( order.state ) + " WHERE order_id = " + order.orderID;
        mLogger.debug(query);

        execute(query);
    }

    private void store(Shuttle shuttle) const {
        string query = "UPDATE shuttles SET state = " + cast<string>( shuttle.state ) + " WHERE shuttle_id = " + shuttle.shuttleID;
        mLogger.debug(query);

        execute(query);
    }

    // Private members
    private int mConnection;
    private List<IDispatchStep> mDispatchSteps;
    private ILogger mLogger;
    private List<Order> mOrders;
    private List<Shuttle> mShuttles;

    // Private consts
    private string ORDER_QUERY const;
    private string SHUTTLE_QUERY const;
}

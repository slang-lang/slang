
// library imports
import System.Collections.List;
import libLog.Logger;

// project imports
import libs.Database;
import libs.IPCService;
import libs.Order;
import libs.Shuttle;
import DispatchSteps.FilterDispatchableShuttles;
import DispatchSteps.FilterOrdersByPriority;
import DispatchSteps.FilterShuttlesByBatteryLevel;
import DispatchSteps.SortOrdersByPriority;
import DispatchSteps.SortShuttlesByBatteryLevel;
import DispatchSteps.SortShuttlesByDistance;


public object OrderDispatcher {
    public void Constructor(Logger logger) {
        mDispatchSteps = new List<IDispatchStep>();
        mIPCService = new IPCService(ORDERDISPATCHER_QUEUE, ORDERDISPATCHER);
        mLogger = new Logger(cast<ILogger>(logger), "OrderDispatcher");
        mOrders = new List<Order>();
        mShuttles = new List<Shuttle>();

        ORDER_QUERY = "SELECT * FROM orders WHERE order_state_id = " + string OrderState.New;
        SHUTTLE_QUERY = "SELECT s.*, st.* FROM shuttles s " +
                        "JOIN shuttle_type st ON (st.shuttle_type_id = s.shuttle_type_id) " +
                        "LEFT JOIN orders ord ON (ord.shuttle_id = s.shuttle_id) ";

        init();
    }

    public void dispatch() modify {
        mLogger.info("Dispatching new orders...");

        // loop as long as there are free shuttles and dispatchable orders available
        while ( true ) {
            loadOrders();
            loadShuttles();

            var data = new DispatchData( cast<Object>( mOrders ), cast<Object>( mShuttles) );
            if ( mOrders.empty() || mShuttles.empty() ) {
                mLogger.warning("No dispatchable orders found");
                return;
            }

            mLogger.info("Starting new dispatch chain with " + data.orders.size() + " order(s) and " + data.shuttles.size() + " shuttle(s)...");
            printOrders(data);
            printShuttles(data);

            bool assignableOrders = true;

            // run through all dispatch steps as often valid results are still returned
            foreach ( IDispatchStep step : mDispatchSteps ) {
                mLogger.info("Executing step '" + step.getName() + "' with " + cast<string>( data ));

                var newData = step.dispatch(data);

                if ( !newData.isValid() ) {
                    mLogger.debug("No valid result found");
                    assignableOrders = false;
                    break;
                }

                data = newData;

                mLogger.info("Executed step '" + step.getName() + "' with " + cast<string>( data ));

                printOrders(data);
                printShuttles(data);
            }

            if ( !assignableOrders ) {
                mLogger.warning("No dispatchable orders found");
                break;
            }

            var order = data.orders.first();
            var shuttle = data.shuttles.first();

            order.shuttleID = shuttle.shuttleID;
            order.stateID = OrderState.Assigned;
            store(order);

            shuttle.stateID = ShuttleState.OCCUPIED;
            store(shuttle);

            notifyShuttleManager(MSG_WORK_RECEIVED);
        }
    }

    public void loadOrders() modify throws {
        mOrders.clear();

        int result = DB.Execute(ORDER_QUERY);
        while ( mysql_next_row(result) ) {
            mOrders.push_back( new Order(result) );
        }
    }

    public void loadShuttles() modify throws {
        mShuttles.clear();

        int result = DB.Execute(SHUTTLE_QUERY);
        while ( mysql_next_row(result) ) {
            mShuttles.push_back( new Shuttle(result) );
        }
    }

    public void printStats() const {
        print("Orders: " + mOrders.size());
        print("Shuttles: " + mShuttles.size());
    }

    private void init() modify {
        mLogger.info("Initializing...");

        initDispatchSteps();
    }

    private void initDispatchSteps() modify {
        mLogger.info("Initializing dispatch steps...");

        mDispatchSteps.push_back( cast<IDispatchStep>( new FilterDispatchableShuttles() ) );
        mDispatchSteps.push_back( cast<IDispatchStep>( new SortShuttlesByBatteryLevel() ) );
        mDispatchSteps.push_back( cast<IDispatchStep>( new FilterShuttlesByBatteryLevel() ) );
        mDispatchSteps.push_back( cast<IDispatchStep>( new SortOrdersByPriority() ) );
        mDispatchSteps.push_back( cast<IDispatchStep>( new FilterOrdersByPriority() ) );
        mDispatchSteps.push_back( cast<IDispatchStep>( new SortShuttlesByDistance() ) );
    }

    private void notifyShuttleManager(string message) modify {
        mIPCService.send(SHUTTLEMANAGER_QUEUE, SHUTTLEMANAGER, message);
    }

    private void printOrders(DispatchData data) modify {
        foreach ( Order order : data.orders ) {
            mLogger.debug( cast<string>( order ) );
        }
    }

    private void printShuttles(DispatchData data) modify {
        foreach ( Shuttle shuttle : data.shuttles ) {
            mLogger.debug( cast<string>( shuttle ) );
        }
    }

    private void store(Order order) modify {
        string query = "UPDATE orders SET sequence = " + order.sequence + ", shuttle_id = " + order.shuttleID + ", order_state_id = " + cast<string>( order.stateID ) + " WHERE order_id = " + order.orderID;
        mLogger.debug(query);

        DB.Execute(query);
    }

    private void store(Shuttle shuttle) modify {
        string query = "UPDATE shuttles SET shuttle_state_id = " + cast<string>( shuttle.stateID ) + " WHERE shuttle_id = " + shuttle.shuttleID;
        mLogger.debug(query);

        DB.Execute(query);
    }

    // Private members
    private List<IDispatchStep> mDispatchSteps;
    private IPCService mIPCService;
    private Logger mLogger;
    private List<Order> mOrders;
    private List<Shuttle> mShuttles;

    // Private consts
    private string ORDER_QUERY const;
    private string SHUTTLE_QUERY const;
}


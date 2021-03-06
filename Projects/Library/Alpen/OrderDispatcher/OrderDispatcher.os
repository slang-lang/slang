
// library imports
import System.Collections.List;
import System.Collections.Set;
import libLog.Logger;

// project imports
import libs.Database;
import libs.IPCService;
import libs.Order;
import libs.Shuttle;
import libs.Storage;
import DispatchSteps.FilterDispatchableShuttles;
import DispatchSteps.FilterOrdersByPriority;
import DispatchSteps.FilterShuttlesByBatteryLevel;
import DispatchSteps.SortOrdersByPriority;
import DispatchSteps.SortShuttlesByBatteryLevel;
import DispatchSteps.SortShuttlesByDistance;


private object Plan const {
    public int costs const;
    public List<Order> orders const;
    public List<Shuttle> shuttles const;

    public void Constructor(List<Order> orders, List<Shuttle> shuttles, int costs) {
        this.costs = costs;
        this.orders = orders;
        this.shuttles = shuttles;
    }

    public bool operator<(Plan other const) const {
/*
        if ( shuttles.size() == other.shuttles.size() ) {
            return orders.size() > other.orders.size();
        }

        return shuttles.size() > other.shuttles.size();
*/

        return costs < other.costs;
    }
}

public object OrderDispatcher {
    public void Constructor(ILogger logger, IPCService ipcService) {
        mDispatchSteps = new List<IDispatchStep>();
        mIPCService = ipcService;
        mLogger = new Logger(logger, "OrderDispatcher");
        mOrders = new List<Order>();
        mShuttles = new List<Shuttle>();
        mStorage = new Storage();

        ORDER_QUERY = "SELECT * FROM orders WHERE order_state_id = " + cast<string>( OrderState.New );
        PARKINGPOSITION = new Position(1, 0);

        init();
    }

    public void ChargeBatteries() modify {
        mLogger.info("Send shuttles battery charging...");

        handleUnoccupiedShuttles();
    }

    public void dispatch(IPCMessage message = null) modify {
        mLogger.info("Dispatching orders...");

        if ( message ) {
            if ( message.message == "CHARGE" ) {
                ChargeBatteries();
            }
        }

        // loop as long as there are free shuttles and dispatchable orders available
        while ( true ) {
            loadOrders();
            loadShuttles();

            mLogger.info("Starting new dispatch chain with " + mOrders.size() + " order(s) and " + mShuttles.size() + " shuttle(s)...");

            if ( mOrders.empty() || mShuttles.empty() ) {
                mLogger.warning("No dispatchable orders found");
                break;
            }

            var data = new DispatchData( mOrders, mShuttles );
            printOrders(data);
            printShuttles(data);

            bool foundAssignableOrders = true;

            // run through all dispatch steps as often as valid results are returned
            foreach ( IDispatchStep step : mDispatchSteps ) {
                mLogger.info("Executing step '" + step.getName() + "' with " + cast<string>( data ));

                var newData = step.dispatch(data);

                if ( !newData.isValid() ) {
                    mLogger.debug("No valid result found");
                    foundAssignableOrders = false;
                    break;
                }

                data = newData;
                assert(data);

                mLogger.info("Executed step '" + step.getName() + "' with " + cast<string>( data ));

                printOrders(data);
                printShuttles(data);
            }

            if ( !foundAssignableOrders ) {
                mLogger.warning("No assignable orders found");
                break;
            }

            var order = data.orders.first();
            var shuttle = data.shuttles.first();

            order.shuttleID = shuttle.shuttleID;
            order.stateID = OrderState.Assigned;
            mStorage.Update(order);

            shuttle.stateID = ShuttleState.OCCUPIED;
            mStorage.Update(shuttle);

            notifyShuttleManager(MSG_WORK_RECEIVED);
        }

        //handleUnoccupiedShuttles();

        mLogger.info("Finished dispatching orders...");
    }

    public void loadOrders() modify throws {
        mOrders.clear();

        int result = DB.Query( ORDER_QUERY );
        while ( mysql_fetch_row(result) ) {
            mOrders.push_back( mStorage.LoadOrderByID( cast<int>( mysql_get_field_value(result, "order_id") ) ) );

            mLogger.info( cast<string>( mOrders.last() ) );
        }
    }

    private void loadShuttles() modify throws {
        mShuttles.clear();

        int result = DB.Query( SHUTTLE_QUERY );
        while ( mysql_fetch_row(result) ) {
            mShuttles.push_back( mStorage.LoadShuttleByID( cast<int>( mysql_get_field_value(result, "shuttle_id") ) ) );

            mLogger.info( cast<string>( mShuttles.last() ) );
        }
    }

    private void handleUnoccupiedShuttles() modify {
        mLogger.info("Start handling unoccupied shuttles...");

        foreach ( Shuttle shuttle : mShuttles ) {
            if ( shuttle.hasWork() ) {
                continue;
            }

            if ( shuttle.position != PARKINGPOSITION ) {
                sendToParkingSpot(shuttle);
            }
        }

        mLogger.info("Finished handling unoccupied shuttles.");
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
        mIPCService.send(SHUTTLEMANAGER_QUEUE, message);
    }

    private void plan() modify {
        // creates a set of plans that are compared to each other and executes the best plan

        var plans = new Set<Plan>();


    }

    private void printOrders(DispatchData data) modify {
        assert( data.orders );

        mLogger.debug("printOrders(" + data.orders.size() + ")");

        foreach ( Order order : data.orders ) {
            mLogger.debug( cast<string>( order ) );
        }
    }

    private void printShuttles(DispatchData data) modify {
        assert( data.shuttles );

        mLogger.debug("printShuttles(" + data.shuttles.size() + ")");

        foreach ( Shuttle shuttle : data.shuttles ) {
            mLogger.debug( cast<string>( shuttle ) );
        }
    }

    private void sendToParkingSpot(Shuttle shuttle) modify {
        mLogger.info("sendToParkingSpot(" + cast<string>( shuttle ) + ")");

        var order = new Order();
        order.stateID = OrderState.Assigned;
        order.orderTypeID = OrderType.Park;
        order.shuttleID = shuttle.shuttleID;
        mStorage.Insert(order);

        var job = new Job();
        job.stateID = JobState.New;
        job.typeID = JobType.Park;
        job.orderID = DB.getLastInsertId();
        job.position = PARKINGPOSITION;
        job.shuttleID = shuttle.shuttleID;
        mStorage.Insert(job);

        order.jobs.push_back( job );

        shuttle.stateID = ShuttleState.OCCUPIED;
        mStorage.Update(shuttle);

        notifyShuttleManager(MSG_WORK_RECEIVED);
    }

    // Private members
    private List<IDispatchStep> mDispatchSteps;
    private IPCService mIPCService;
    private Logger mLogger;
    private List<Order> mOrders;
    private List<Shuttle> mShuttles;
    private Storage mStorage;

    // Private consts
    private string ORDER_QUERY const;
    private Position PARKINGPOSITION const;
}


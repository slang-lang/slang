#!/usr/local/bin/slang

// library imports
import libParam.ParameterHandler;

// project imports
import libs.Database;
import libs.Job;
import libs.Order;


public void Main(int argc, string args) {
	try {
		var params = new ParameterHandler(argc, args);
		var order = new Order();

		if ( params.contains("OrderTypeID") ) {
			order.orderTypeID = OrderType cast<int>( params.getParameter("OrderTypeID").Value );
		}
		else {
			cout("OrderTypeID: ");
			order.orderTypeID = OrderType cast<int>( cin() );
		}

		if ( params.contains("Priority") ) {
			order.priority = cast<int>( params.getParameter("Priority").Value );
		}
		else {
			cout("Priority: ");
			order.priority = cast<int>( cin() );
		}

		if ( params.contains("Sequence") ) {
			order.sequence = cast<int>( params.getParameter("Sequence").Value );
		}
		else {
			cout("Sequence: ");
			order.sequence = cast<int>( cin() );
		}


		DB.Connect();
		DB.Execute( "BEGIN" );

		DB.Insert( "INSERT INTO orders (order_type_id, priority, sequence) VALUES (" + cast<string>( order.orderTypeID ) + ", " + order.priority + ", " + order.sequence + ")" );

		switch ( order.orderTypeID ) {
			case OrderType.Park: {
				createParkOrder( getLastInsertId() );
				break;
			}
			case OrderType.Transport: {
				createTransportOrder( getLastInsertId() );
				break;
			}
		}

		DB.Execute( "COMMIT" );
	}
	catch ( string e ) {
		print("Exception: " + e);

		DB.Execute( "ROLLBACK" );
	}
	catch ( IException e ) {
		print("Exception: " + e.what());

		DB.Execute( "ROLLBACK" );
	}
	finally {
		DB.Disconnect();
	}
}

private void createParkOrder(int orderID) const {
	if ( !orderID ) {
		print("Invalid orderID provided!");
		return;
	}

	var job = new Job();
	job.typeID = JobType.Park;
	job.orderID = orderID;
	job.sequence = 1;

	createJob(job);
}

private void createJob(Job job) const {
	if ( !job.levelID ) {
		cout("LevelID: ");
		job.position.levelID = cast<int>( cin() );
	}

	if ( !job.position.positionID ) {
		cout("PositionID: ");
		job.position.positionID = cast<int>( cin() );
	}

	if ( !job.sequence ) {
		cout("Sequence: ");
		job.sequence = cast<int>( cin() );
	}

	DB.Insert( "INSERT INTO jobs (order_id, job_type_id, job_state_id, level_id, position_id, sequence) " +
		   "VALUES (" + job.orderID + ", " + cast<string>( job.typeID ) + ", " + cast<string>( JobState.New ) + ", " + job.position.levelID + ", " + job.position.positionID + ", " + job.sequence + ")" );

}

private void createTransportOrder(int orderID) const {
	if ( !orderID ) {
		print("Invalid orderID provided!");
		return;
	}

	var getJob = new Job();
	getJob.typeID = JobType.Get;
	getJob.orderID = orderID;
	getJob.sequence = 1;
	createJob(getJob);

	var putJob = new Job();
	putJob.typeID = JobType.Put;
	putJob.orderID = orderID;
	putJob.sequence = 2;
	createJob(putJob);
}

private int getLastInsertId() const {
	int result = DB.Query( "SELECT LAST_INSERT_ID() AS ID" );

	if ( mysql_next_row(result) ) {
		return int mysql_get_field_value(result, "ID");
	}

	return 0;
}


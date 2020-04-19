#!/usr/local/bin/slang

// Library imports
import System.Collections.Map;

// Project imports
import Config;
import DatatypeMapper;


public object Generator {
	private int mDatabaseHandle = 0;
	private DatatypeMapper mDatatypeMapper;

	public void Constructor(int dbHandle) {
		mDatabaseHandle = dbHandle;
		mDatatypeMapper = new DatatypeMapper();
	}

	public Map<string, string> generate(string table) throws {
		string query = "SELECT TABLE_NAME, COLUMN_NAME, DATA_TYPE "
			     + "FROM INFORMATION_SCHEMA.COLUMNS "
			     + "WHERE 1 = 1 "
			     + "AND TABLE_SCHEMA = '" + Database + "' "
			     + "AND TABLE_NAME = '" + table + "' "
			     + "ORDER BY TABLE_NAME ASC";

		int error = mysql_query(mDatabaseHandle, query);
		if ( error ) {
			throw mysql_error(mDatabaseHandle);
		}

		var resultTable = new Map<string, string>();

		int result = mysql_store_result(mDatabaseHandle);
		while ( mysql_next_row(result) ) {
			string column = mysql_get_field_value(result, "COLUMN_NAME");
			string type = mysql_get_field_value(result, "DATA_TYPE");

			//print(type + " " + column + " => " + mDatatypeMapper.lookupType(type) + " " + column);

			try {
				resultTable.insert(column, mDatatypeMapper.lookupType(type));
			}
			catch ( IException e ) {
				print("Exception: " + e.what());
			}
		}

		return resultTable;
	}
}


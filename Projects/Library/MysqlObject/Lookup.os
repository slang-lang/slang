
// Library imports
import System.Collections.List;
import System.String;

// Project imports


public object Lookup {
	private int mDatabaseHandle;

	public void Constructor(int dbHandle) {
		mDatabaseHandle = dbHandle;
	}

	public List<string> getTables(string database) const throws {
		string query = "SHOW FULL TABLES IN " + database + " WHERE TABLE_TYPE LIKE 'BASE TABLE'";

		int error = mysql_query(mDatabaseHandle, query);
		if ( error ) {
			throw mysql_error(mDatabaseHandle);
		}

		var tables = new List<string>();

		int result = mysql_store_result(mDatabaseHandle);
		while ( mysql_next_row(result) ) {
			string table = mysql_get_field_value(result, 0);

			tables.push_back(table);
		}

		return tables;
	}

	public List<string> getViews(string database) const throws {
		string query = "SHOW FULL TABLES IN " + database + " WHERE TABLE_TYPE LIKE 'VIEW'";

		int error = mysql_query(mDatabaseHandle, query);
		if ( error ) {
			throw mysql_error(mDatabaseHandle);
		}

		var tables = new List<string>();

		int result = mysql_store_result(mDatabaseHandle);
		while ( mysql_next_row(result) ) {
			string table = mysql_get_field_value(result, 0);

			tables.push_back(table);
		}

		return tables;
	}
}


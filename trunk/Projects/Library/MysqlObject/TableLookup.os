
// Library imports
import System.Collections.List;
import System.String;

// Project imports


public object TableLookup {
	private int mDatabaseHandle;

	public void Constructor(int dbHandle) {
		mDatabaseHandle = dbHandle;
	}

	public List<String> getTables(string database) const throws {
		string query = "SELECT TABLE_NAME "
			     + "FROM INFORMATION_SCHEMA.COLUMNS "
			     + "WHERE TABLE_SCHEMA = '" + database + "' "
			     + "GROUP BY TABLE_NAME "
			     + "ORDER BY TABLE_NAME ASC";

		int error = mysql_query(mDatabaseHandle, query);
		if ( error ) {
			throw mysql_error(mDatabaseHandle);
		}

		var tables = new List<String>();

		int result = mysql_store_result(mDatabaseHandle);
		while ( mysql_next_row(result) ) {
			string table = mysql_get_field_value(result, "TABLE_NAME");

			tables.push_back(new String(table));
		}

		return tables;
	}
}


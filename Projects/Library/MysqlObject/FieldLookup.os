
// Library imports
import System.Collections.Map;

// Project imports
import Config;
import DatatypeMapper;


public object FieldLookup {
	public void Constructor() {
		mDatatypeMapper = new DatatypeMapper();
	}

	public Map<string, string> getFields( int databaseHandle, string entityName ) const throws {
		string query = "SELECT TABLE_NAME, COLUMN_NAME, DATA_TYPE \
						FROM INFORMATION_SCHEMA.COLUMNS \
						WHERE TABLE_SCHEMA = '" + Database + "' \
						AND TABLE_NAME = '" + entityName + "' \
						ORDER BY TABLE_NAME ASC, COLUMN_NAME ASC";

		int error = mysql_query( databaseHandle, query );
		if ( error ) {
			throw mysql_error( databaseHandle );
		}

		var resultTable = new Map<string, string>();

		int result = mysql_store_result( databaseHandle );
		while ( mysql_next_row( result ) ) {
			string column = mysql_get_field_value( result, "COLUMN_NAME" );
			string type = mysql_get_field_value( result, "DATA_TYPE" );

			try {
				resultTable.insert( column, mDatatypeMapper.lookupType( type ) );
			}
			catch ( IException e ) {
				print( "Exception: " + e.what() );
			}
		}

		return resultTable;
	}

	private DatatypeMapper mDatatypeMapper;
}


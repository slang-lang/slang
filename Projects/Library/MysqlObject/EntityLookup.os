
// Library imports
import System.Collections.List;
import System.String;

// Project imports


public object EntityLookup {
	private int mDatabaseHandle;

	public void Constructor( int dbHandle ) {
		mDatabaseHandle = dbHandle;
	}

	public List<string> getTables( string database ) const throws {
		return getEntitiesByType( database, "BASE TABLE" );
	}

	public List<string> getViews( string database ) const throws {
		return getEntitiesByType( database, "VIEW" );
	}

	private List<string> getEntitiesByType( string database, string entityType ) const throws {
		string query = "SHOW FULL TABLES IN " + database + " WHERE TABLE_TYPE LIKE '" + entityType + "'";

		int error = mysql_query( mDatabaseHandle, query );
		if ( error ) {
			throw mysql_error( mDatabaseHandle );
		}

		var entities = new List<string>();

		int result = mysql_store_result( mDatabaseHandle );
		while ( mysql_next_row( result ) ) {
			entities.push_back( mysql_get_field_value( result, 0 ) );
		}

		return entities;
	}
}


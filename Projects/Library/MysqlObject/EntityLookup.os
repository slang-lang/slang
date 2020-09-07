
// Library imports
import System.Collections.List;
import System.String;

// Project imports


public object EntityLookup {
	public List<string> getTables( int databaseHandle, string database ) const throws {
		return getEntitiesByType( databaseHandle, database, "BASE TABLE" );
	}

	public List<string> getViews( int databaseHandle, string database ) const throws {
		return getEntitiesByType( databaseHandle, database, "VIEW" );
	}

	public List<string> getEntitiesByType( int databaseHandle, string database, string entityType ) const throws {
		string query = "SHOW FULL TABLES IN " + database + " WHERE TABLE_TYPE LIKE '" + entityType + "'";

		int error = mysql_query( databaseHandle, query );
		if ( error ) {
			throw mysql_error( databaseHandle );
		}

		var entities = new List<string>();

		int result = mysql_store_result( databaseHandle );
		while ( mysql_fetch_row( result ) ) {
			entities.push_back( mysql_get_field_value( result, 0 ) );
		}

		return entities;
	}
}


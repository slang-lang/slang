
// Library imports
import System.Collections.Vector;
import System.String;

// Project imports


public object TokenEntity {
	public int Id const;
	public string Token const;

	public void Constructor( int id, string token ) {
		Id = id;
		Token = token;
	}
}

public object TokenLookup {
	public Vector<TokenEntity> getTokens( int databaseHandle, string database, string table ) const throws {
		var query = "SELECT * FROM " + database + "." + table + " ORDER BY id ASC";

		var error = mysql_query( databaseHandle, query );
		if ( error ) {
			throw mysql_error( databaseHandle );
		}

		var tokens = new Vector<TokenEntity>();

		var result = mysql_store_result( databaseHandle );
		while ( mysql_fetch_row( result ) ) {
			tokens.push_back( new TokenEntity(
				cast<int>( mysql_get_field_value( result, "id" ) ),
				mysql_get_field_value( result, "token" )
			) );
		}

		return tokens;
	}
}



import System.Collections.Map;

public object KeyLookup<K, V> {
	public void Constructor( int databaseHandle, string query = "" ) {
		Collection = new Map<K, V>();
		DB = databaseHandle;

		if ( query ) {
			loadByQuery( query );
		}
	}

	public bool contains( K index ) const {
		return Collection.contains( index );
	}

	public V get( K index const ) const throws {
		return Collection.get( index );
	}

	public void loadByQuery( string query ) modify throws {
		var error = mysql_query( DB, query );
		if ( error ) {
			throw mysql_error( DB );
		}

		Collection.clear();

		var result = mysql_store_result( DB );
		while ( mysql_fetch_row( result ) ) {
			var record = new V( DB );
			record.loadByResult( result );

			Collection.insert( K record.KeyId, record );
		}
	}

	private Map<K, V> Collection;
	private int DB const;
}


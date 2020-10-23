
// Library imports
import System.Collections.Map;
import System.Collections.Vector;

// Project imports
import Config;
import DatatypeMapper;
import Utils;


public object FieldEntry const {
	public string DataType const;
	public string PrettyName const;
	public string RealName const;

	public void Constructor( string realName, string prettyName, string dataType ) {
		DataType = dataType;
		PrettyName = prettyName;
		RealName = realName;
	}

	public bool operator==( string realName ) const {
		return RealName == realName;
	}

	public string =operator( string ) const {
		return "FieldEntry { 'RealName': '" + RealName + "', PrettyName': '" + PrettyName + "', 'DataType': '" + DataType + "'";
	}
}

public object FieldLookup {
	public void Constructor() {
		mDatatypeMapper = new DatatypeMapper();
	}

	public Vector<FieldEntry> getFields( int databaseHandle, string entityName ) const throws {
		string query = "SELECT TABLE_NAME, COLUMN_NAME, DATA_TYPE \
						FROM INFORMATION_SCHEMA.COLUMNS \
						WHERE TABLE_SCHEMA = '" + Config.Database + "' \
						AND TABLE_NAME = '" + entityName + "' \
						ORDER BY TABLE_NAME ASC, COLUMN_NAME ASC";

		int error = mysql_query( databaseHandle, query );
		if ( error ) {
			throw mysql_error( databaseHandle );
		}

		var collection = new Vector<FieldEntry>();

		int result = mysql_store_result( databaseHandle );
		while ( mysql_fetch_row( result ) ) {
			string column = mysql_get_field_value( result, "COLUMN_NAME" );
			string type = mysql_get_field_value( result, "DATA_TYPE" );

			try {
				collection.push_back( new FieldEntry( column, Utils.prettify( column ), mDatatypeMapper.lookupType( type ) ) );
			}
			catch ( IException e ) {
				print( "Exception: " + e.what() );
			}
		}

		return collection;
	}

	private DatatypeMapper mDatatypeMapper;
}


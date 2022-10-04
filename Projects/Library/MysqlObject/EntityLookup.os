
// Library imports
import System.Collections.Map;
import System.Collections.Vector;
import System.String;

// Project imports
import Consts;
import DatatypeMapper;
import FieldLookup;
import TokenLookup;


public object EntityType {
	public Vector<FieldEntry> Fields const;
	public bool HasLookup const;
	public string Name const;
	public Vector<TokenEntity> Tokens const;
	public string Type const;

	public void Constructor( string name, string type, bool hasLookup, Vector<FieldEntry> fields, Vector<TokenEntity> tokens ) {
		Fields = fields;
		HasLookup = hasLookup;
		Name = name;
		Tokens = tokens;
		Type = type;
	}

	public string =operator( string ) const {
		return Name;
	}
}

public object EntityLookup {
	public void Constructor( int databaseHandle, string databaseName ) {
		mDatabaseHandle = databaseHandle;
		mDatabaseName = databaseName;
		mFieldLookup = new FieldLookup();
		mTokenLookup = new TokenLookup();
	}

	public void fetchEntities() modify {
		mFunctions  = fetchFunctions();
		mProcedures = fetchProcedures();
		mTables     = getEntitiesByType( "BASE TABLE" );
		mViews      = getEntitiesByType( "VIEW" );
	}

	public EntityType getEntity( string entityName ) const throws {
		if ( mTables.contains( entityName ) ) {
			return mTables[ entityName ];
		}

		return mViews[ entityName ];
	}

	public Vector<string> getFunctions() const {
		return mFunctions;
	}

	public Vector<string> getProcedures() const {
		return mProcedures;
	}

	public Map<string, EntityType> getTables() const {
		return mTables;
	}

	public Map<string, EntityType> getViews() const {
		return mViews;
	}

	private Map<string, EntityType> getEntitiesByType( string entityType ) const throws {
		var query = "SHOW FULL TABLES IN " + mDatabaseName + " WHERE TABLE_TYPE LIKE '" + entityType + "'";

		var error = mysql_query( mDatabaseHandle, query );
		if ( error ) {
			throw mysql_error( mDatabaseHandle );
		}

		var entities = new Map<string, EntityType>();

		var result = mysql_store_result( mDatabaseHandle );
		while ( mysql_fetch_row( result ) ) {
			var name = mysql_get_field_value( result, 0 );

			var fields = mFieldLookup.getFields( mDatabaseHandle, name );

			bool hasId;
			bool hasToken;
			foreach ( FieldEntry field : fields ) {
				if ( field.RealName == PrimaryKeyName ) {
					hasId = true;
				}
				else if ( field.RealName == TokenKeyName ) {
					hasToken = true;
				}
			}

			Vector<TokenEntity> tokens;
			if ( hasId && hasToken ) {
				tokens = mTokenLookup.getTokens( mDatabaseHandle, mDatabaseName, name );
			}

			entities.insert( name, new EntityType( name, entityType, ( hasId && hasToken ), fields, tokens ) );
		}

		return entities;
	}

	private Vector<string> fetchFunctions() const throws {
		var query = "SHOW FUNCTION STATUS WHERE DB = '" + mDatabaseName + "'";

		var error = mysql_query( mDatabaseHandle, query );
		if ( error ) {
			throw mysql_error( mDatabaseHandle );
		}

		var entities = new Vector<string>();

		var result = mysql_store_result( mDatabaseHandle );
		while ( mysql_fetch_row( result ) ) {
			var name = mysql_get_field_value( result, 1 );

			entities.push_back( name );
		}

		return entities;
	}

	private Vector<string> fetchProcedures() const throws {
		var query = "SHOW PROCEDURE STATUS WHERE DB = '" + mDatabaseName + "'";

		var error = mysql_query( mDatabaseHandle, query );
		if ( error ) {
			throw mysql_error( mDatabaseHandle );
		}

		var entities = new Vector<string>();

		var result = mysql_store_result( mDatabaseHandle );
		while ( mysql_fetch_row( result ) ) {
			var name = mysql_get_field_value( result, 1 );

			entities.push_back( name );
		}

		return entities;
	}

	private int mDatabaseHandle;
	private string mDatabaseName;
	private FieldLookup mFieldLookup;
	private Vector<string> mFunctions;
	private Vector<string> mProcedures;
	private Map<string, EntityType> mTables;
	private TokenLookup mTokenLookup;
	private Map<string, EntityType> mViews;
}


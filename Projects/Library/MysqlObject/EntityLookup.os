
// Library imports
import System.Collections.List;
import System.Collections.Map;
import System.String;

// Project imports
import Consts;
import FieldLookup;
import TokenLookup;


public object EntityType {
	public Vector<FieldEntry> Fields const;
	public bool HasLookup const;
	public string Name const;
	public List<TokenEntity> Tokens const;
	public string Type const;

	public void Constructor( string name, string type, bool hasLookup, Vector<FieldEntry> fields, List<TokenEntity> tokens ) {
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
		mTables = getEntitiesByType( "BASE TABLE" );
		mViews = getEntitiesByType( "VIEW" );
	}

	public EntityType getEntity( string entityName ) const {
		if ( mTables.contains( entityName ) ) {
			return mTables[ entityName ];
		}

		return mViews[ entityName ];
	}

	public Map<string, EntityType> getTables() const {
		return mTables;
	}

	public Map<string, EntityType> getViews() const {
		return mViews;
	}

	private Map<string, EntityType> getEntitiesByType( string entityType ) const throws {
		string query = "SHOW FULL TABLES IN " + mDatabaseName + " WHERE TABLE_TYPE LIKE '" + entityType + "'";

		int error = mysql_query( mDatabaseHandle, query );
		if ( error ) {
			throw mysql_error( mDatabaseHandle );
		}

		var entities = new Map<string, EntityType>();

		int result = mysql_store_result( mDatabaseHandle );
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

			List<TokenEntity> tokens;
			if ( hasId && hasToken ) {
				tokens = mTokenLookup.getTokens( mDatabaseHandle, mDatabaseName, name );
			}

			entities.insert( name, new EntityType( name, entityType, ( hasId && hasToken ), fields, tokens ) );
		}

		return entities;
	}

	private int mDatabaseHandle;
	private string mDatabaseName;
	private FieldLookup mFieldLookup;
	private TokenLookup mTokenLookup;

	private Map<string, EntityType> mTables;
	private Map<string, EntityType> mViews;
}


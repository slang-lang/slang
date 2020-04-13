
// Library imports
import System.Collections.List;

// Project imports
import Exceptions;

public namespace Mysql { }

public object MysqlRow {
// Public

	public void Constructor( int handle ) {
		mHandle = handle;
		mNumFields = mysql_num_fields( handle );
	}

	public string getName( int index ) const throws {
		return mysql_get_field_name( mHandle, index );
	}

	public string getValue( int index ) const throws {
		return mysql_get_field_value( mHandle, index );
	}

	public string getValue( string name ) const throws {
		return mysql_get_field_value( mHandle, name );
	}

	public int numFields() const {
		return mNumFields;
	}

// Private

	private int mHandle const;
	private int mNumFields const;
}


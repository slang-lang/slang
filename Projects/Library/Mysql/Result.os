
// Library imports
import System.Collections.List;

// Project imports
import Exceptions;
import Row;

public namespace Mysql { }

public object MysqlResult implements ICollection, IIterable {
// Public

	public void Constructor( int handle ) {
		mHandle = handle;
		mNumFields = mysql_num_fields( mHandle );
		mNumRows = mysql_num_rows( mHandle );

		//print( "Handle: " + mHandle + ", NumFields: " + mNumFields + ", NumRows: " + mNumRows );
	}

	public MysqlRow at( int index ) modify throws {
		if ( index < 0 || index >= mNumRows ) {
			throw new MysqlException( "index(" + index + ") out of bounds!" );
		}

		return new MysqlRow( mysql_row_seek( mHandle, index ) );
	}

	public bool empty() const {
		return mNumRows == 0;
	}

	public Iterator<MysqlRow> getIterator() const {
		return new Iterator<MysqlRow>( cast<ICollection>( this ) );
	}

	public int numFields() const {
		return mNumFields;
	}

	public int numRows() const {
		return mNumRows;
	}

	public int size() const {
		return mNumRows;
	}

	public MysqlRow operator[]( int index ) modify throws {
		return at( index );
	}

// Private

	private int mHandle const;
	private int mNumFields const;
	private int mNumRows const;
}


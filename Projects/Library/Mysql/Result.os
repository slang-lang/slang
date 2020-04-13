
// Library imports
import System.Collections.Iterator;

// Project imports
import Exceptions;
import Row;

public namespace Mysql { }

public object MysqlResult implements Iterator<MysqlRow> {
// Public

	public void Constructor( int handle ) {
		mCurrentIndex = -1;
		mHandle = handle;
		mNumFields = mysql_num_fields( handle );
		mNumRows = mysql_num_rows( handle );
	}

	public void Destructor() {
		if ( mHandle ) {
			// free result after using it
			mysql_free_result( mHandle );
		}
	}

	public MysqlRow at( int index ) const throws {
		if ( index < 0 || index >= mNumRows ) {
			throw new MysqlException( "index(" + index + ") out of bounds!" );
		}

		// seek to the desired row ...
		mysql_data_seek( mHandle, index );
		// ... and fetch its data
		if ( !mysql_fetch_row( mHandle ) ) {
			throw new MysqlException( "invalid row (" + index + ") fetched!" );
		}

		return new MysqlRow( mHandle );
	}

	public MysqlRow current() const throws {
		return at( mCurrentIndex );
	}

	public bool empty() const {
		return mNumRows == 0;
	}

	/*
	 * returns true if the iteration did not reach the last row
	 */
	public bool hasNext() const {
		return mCurrentIndex < mNumRows - 1;
	}

	/*
	 * returns the next row
	 * throws OutOfBoundsException
	 */
	public MysqlRow next() modify throws {
		if ( mCurrentIndex >= mNumRows ) {
			throw new OutOfBoundsException("index(" + mCurrentIndex + ") out of bounds");
		}

		mCurrentIndex++;

		return at( mCurrentIndex );
	}

	public int numFields() const {
		return mNumFields;
	}

	public int numRows() const {
		return mNumRows;
	}

	/*
	 * resets the current iteration
	 */
	public void reset() modify {
		mCurrentIndex = -1;
	}

	public MysqlRow operator[]( int index ) modify throws {
		return at( index );
	}

	/*
	 * returns the value of the current iteration
	 * equivalent to calling current()
	 * throws NotInitializedException, OutOfBoundsException
	 */
	public MysqlRow =operator(string) const throws {
		return current();
	}

	/*
	 * Equality operator
	 */
	public bool operator==(MysqlResult other const) const {
		return mHandle == other.mHandle && mCurrentIndex == other.mCurrentIndex;
	}

	/*
	 * returns the next sub string of the held String value
	 * equivalent to calling next()
	 * throws OutOfBoundsException
	 */
	public MysqlRow operator++() modify throws {
		return next();
	}

// Private

	private int mCurrentIndex;
	private int mHandle const;
	private int mNumFields const;
	private int mNumRows const;
}



// Library imports
import System.Collections.Iterator;

// Project imports
import Exceptions;

public namespace Mysql { }

public object MysqlRow { //implements Iterator<string> {
// Public

	public void Constructor( int handle ) {
		mHandle = handle;
		mNumFields = mysql_num_fields( handle );

		reset();
	}

	public string at( int index ) const throws {
		if ( index < 0 || index >= mNumFields ) {
			throw new MysqlException( "index (" + index + ") out of bounds!" );
		}

		return getValue( index );
	}

	public string current() const {
		return at( mCurrentIndex );
	}

	public bool empty() const {
		return mNumFields == 0;
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

	public bool hasNext() const {
		return mCurrentIndex < mNumFields - 1;
	}

	/*
	 * returns the next value
	 * throws OutOfBoundsException
	 */
	public string next() modify throws {
		if ( mCurrentIndex >= mNumFields ) {
			throw new OutOfBoundsException("index(" + mCurrentIndex + ") out of bounds");
		}

		mCurrentIndex++;

		return at( mCurrentIndex );
	}

	public int numFields() const {
		return mNumFields;
	}

	public void reset() modify {
		mCurrentIndex = -1;
	}

	public string operator[]( int index ) const {
		return at( index );
	}

	/*
	 * Equality operator
	 */
	public bool operator==(MysqlRow other const) const {
		return mHandle == other.mHandle && mCurrentIndex == other.mCurrentIndex;
	}

	/*
	 * returns the next value
	 * equivalent to calling next()
	 * throws OutOfBoundsException
	 */
	public string operator++() modify throws {
		return next();
	}

// Private

	private int mCurrentIndex;
	private int mHandle const;
	private int mNumFields const;
}


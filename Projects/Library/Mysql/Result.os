
// Library imports
import System.Collections.List;

// Project imports
import Entry;
import Exceptions;
import Row;

public namespace Mysql { }

public object MysqlResult implements ICollection, IIterable {
// Public interface

	public void Constructor(int handle) {
		mCurrentRowIdx = -1;
		mHandle = handle;
		mNumFields = mysql_num_fields(mHandle);
		mNumRows = mysql_num_rows(mHandle);
		mRows = new List<MysqlRow>();

		initialize();
	}

	public MysqlRow at(int index) const throws {
		return mRows.at(index);
	}

	public bool empty() const {
		return mNumRows == 0;
	}

	public MysqlRow getCurrentRow() const throws {
		if ( mCurrentRowIdx == -1 ) {
			throw new MysqlException("not initialized!");
		}

		return mCurrentRow;
	}

	public MysqlEntry getField(string name) const throws {
		if ( mCurrentRowIdx == -1 ) {
			throw new MysqlException("not initialized!");
		}

		return mCurrentRow.getField(name);
	}

	public Iterator<MysqlRow> getIterator() const {
		return new Iterator<MysqlRow>(ICollection this);
	}

	public bool hasNext() const {
		return mCurrentRowIdx < mNumRows;
	}

	public MysqlRow next() modify throws {
		if ( mCurrentRowIdx >= mNumRows ) {
			throw new MysqlException("index(" + mCurrentRowIdx + ") out of bounds!");
		}

		mCurrentRow = mRows.at(mCurrentRowIdx);

		return mCurrentRow;
	}

	public int numFields() const {
		return mNumFields;
	}

	public int numRows() const {
		return mNumRows;
	}

	public void reset() modify {
		delete mCurrentRow;
		mCurrentRowIdx = -1;
	}

	public int size() const {
		return mNumRows;
	}

// Private
	private void initialize() modify throws {
		// prefetch data
		for ( int idx = 0; idx < mNumRows; idx++ ) {
			if ( !mysql_next_row(mHandle) ) {
				throw new MysqlException("error while fetching row(" + idx + ")!");
			}

			mRows.push_back(
				new MysqlRow(mHandle)
			);
		}
	}

	private MysqlRow mCurrentRow;
	private int mCurrentRowIdx;
	private int mHandle const;
	private int mNumFields const;
	private int mNumRows const;
	private List<MysqlRow> mRows;
}


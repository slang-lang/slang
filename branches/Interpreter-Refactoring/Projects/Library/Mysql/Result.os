
import Entry;
import Exceptions;
import Row;

public namespace Mysql {

	public object Result {
		private int mAffectedRows;
		private int mCurrentFieldIdx;
		private int mCurrentRowIdx;
		private int mHandle;
		private int mNumFields;
		private int mNumRows;

		public void Constructor(int handle) {
			mHandle = handle;

			initialize();
		}

		public string ToString() const {
			return	"Result={ " +
					"Handle=" + mHandle + ", " +
					"AffectedRows=" + mAffectedRows + ", " +
					"NumRows=" + mNumRows + ", " +
					"NumFields=" + mNumFields + ", " +
					"CurrentRowIdx=" + mCurrentRowIdx + ", " +
					"CurrentFieldIdx=" + mCurrentFieldIdx +
				" }";
		}

		public int affectedRows() const {
			return mAffectedRows;
		}

		public Mysql.Row getCurrentRow() const {
			return new Row(mHandle);
		}

		public Mysql.Entry getField(int fieldIdx) const {
			if ( fieldIdx < 0 || fieldIdx > mNumFields ) {
				throw new OutOfBoundsException("fieldIdx out of bounds");
			}

			string name = mysql_get_field_name(mHandle, fieldIdx);
			string value = mysql_get_field_value(mHandle, fieldIdx);

			return new Entry(name, value);
		}

		public Mysql.Entry getField(string name) const {
			Entry entry;	// null object

			for ( int idx = 0; idx < mNumFields; idx = idx + 1 ) {
				if ( mysql_get_field_name(mHandle, idx) == name ) {
					return new Entry(name, mysql_get_field_value(mHandle, idx));
				}
			}

			return entry;
		}

		public void seekRow(int rowIdx) {
			if ( rowIdx < 0 || rowIdx >= mNumRows ) {
				throw new OutOfBoundsException("rowIdx out of bounds");
			}

			mysql_data_seek(mHandle, rowIdx);
		}

		public bool hasNext() const {
			return mCurrentRowIdx < mNumRows;
		}

		private bool initialize() modify {
			mAffectedRows = 0;
			mCurrentFieldIdx = 0;
			mCurrentRowIdx = 0;
			mNumFields = mysql_num_fields(mHandle);
			mNumRows = mysql_num_rows(mHandle);

			return true;
		}

		public bool next() modify {
			bool hasNext = mysql_next_row(mHandle);

			if ( hasNext ) {
				mCurrentRowIdx = mCurrentRowIdx + 1;
			}

			return hasNext;
		}

		public int numFields() const {
			return mNumFields;
		}

		public int numRows() const {
			return mNumRows;
		}
	}

}


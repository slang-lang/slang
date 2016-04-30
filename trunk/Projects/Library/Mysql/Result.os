
//import System.GDI.IResult;
import Entry;
import Exceptions;
import Row;

public namespace Mysql
{
	public object Result //implements System.GDI.IResult
	{
		private int mCurrentFieldIdx;
		private int mCurrentRowIdx;
		private int mHandle;
		private int mNumFields;
		private int mNumRows;

		public void Result() {
			//writeln("Result::Result()");
		}
		public void Result(int handle) {
			//writeln("Result::Result(" + handle + ")");

			mHandle = handle;

			Initialize();
		}

		public void ~Result() {
			//writeln("Result::~Result()");
		}

		public Row GetCurrentRow() const {
			Row row = new Row(mHandle);

			return row;
		}

		public Entry GetField(int fieldIdx) const {
			if ( fieldIdx < 0 || fieldIdx > mNumFields ) {
				throw new OutOfBoundsException("fieldIdx out of bounds");
			}

			string name = mysql_get_field_name(mHandle, fieldIdx);
			string value = mysql_get_field_value(mHandle, fieldIdx);

			return new Entry(name, value);
		}

		public Entry GetField(string name) const {
			for ( int idx = 0; idx < mNumFields; idx = idx + 1 ) {
				if ( mysql_get_field_name(mHandle, idx) == name ) {
					return new Entry(name, mysql_get_field_value(mHandle, idx));
				}
			}

			return new Entry();
		}

		public bool HasNext() const {
			return mCurrentRowIdx < mNumRows;
		}

		private bool Initialize() modify {
			mCurrentFieldIdx = 0;
			mCurrentRowIdx = 0;
			mNumFields = mysql_num_fields(mHandle);
			mNumRows = mysql_num_rows(mHandle);

			return true;
		}

		public void Next() modify {
			if ( !mysql_next_row(mHandle) ) {
				throw new OutOfBoundsException("iterator exceeded result");
			}

			mCurrentRowIdx = mCurrentRowIdx + 1;
		}

		public int NumFields() const {
			return mNumFields;
		}

		public int NumRows() const {
			return mNumRows;
		}
	}
}


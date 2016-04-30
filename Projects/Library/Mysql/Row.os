
import Entry;
import Exceptions;

public namespace Mysql
{
	public object Row
	{
		private int mNumFields;
		private int mResultHandle;

		public void Row(int handle) {
			//writeln("Row::Row(" + handle + ")");

			mResultHandle = handle;

			mNumFields = mysql_num_fields(mResultHandle);
		}
		public void ~Row() {
			//writeln("Row::~Row()");
		}

		public Entry Get(int fieldIdx) {
/*
			if ( fieldIdx < 0 || fieldIdx > mNumFields ) {
				throw new OutOfBoundsException("fieldIdx out of bounds");
			}
*/

			string name = mysql_get_field_name(mResultHandle, fieldIdx);
			string value = mysql_get_field_value(mResultHandle, fieldIdx);

			return new Entry(name, value);
		}

		public string GetName(int fieldIdx) {
/*
			if ( fieldIdx < 0 || fieldIdx > mNumFields ) {
				throw new OutOfBoundsException("fieldIdx out of bounds");
			}
*/

			return mysql_get_field_name(mResultHandle, fieldIdx);
		}

		public string GetType(int fieldIdx) {
/*
			if ( fieldIdx < 0 || fieldIdx > mNumFields ) {
				throw new OutOfBoundsException("fieldIdx out of bounds");
			}
*/
			assert(!"not implemented");
		}

		public string GetValue(int fieldIdx) {
/*
			if ( fieldIdx < 0 || fieldIdx > mNumFields ) {
				throw new OutOfBoundsException("fieldIdx out of bounds");
			}
*/

			return mysql_get_field_value(mResultHandle, fieldIdx);
		}

		public int NumFields() const {
			return mNumFields;
		}

		public string ToString() const {
			string result = "|";

			for ( int i = 0; i < mNumFields; i = i++ ) {
				result = result + " " + GetName(i) + ": " + GetValue(i) + " |";
			}

			return result;
		}
	}
}

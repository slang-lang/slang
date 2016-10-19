
import Entry;
import Exceptions;

public namespace Mysql {

	public object Row {
		private int mNumFields;
		private int mResultHandle;

		public void Row(int handle) {
			mResultHandle = handle;

			mNumFields = mysql_num_fields(mResultHandle);
		}
		public void ~Row() {
		}

		public string ToString() const {
			return "Row={" +
					"mNumFields=" + mNumFields + ", " +
					"mResultHandle=" + mResultHandle + " " +
				"}";
		}

		public Mysql.Entry getEntry(int fieldIdx) {
/*
			if ( fieldIdx < 0 || fieldIdx > mNumFields ) {
				throw new OutOfBoundsException("fieldIdx out of bounds");
			}
*/

			string name = mysql_get_field_name(mResultHandle, fieldIdx);
			string value = mysql_get_field_value(mResultHandle, fieldIdx);

			return new Mysql.Entry(name, value);
		}

		public Mysql.Entry getEntry(string name) {
			for ( int idx = 0; idx < mNumFields; idx = idx++ ) {
				if ( mysql_get_field_name(mResultHandle, idx) == name ) {
					return mysql_get_field_value(mResultHandle, idx);
				}
			}

			return "";
		}

		public string getName(int fieldIdx) {
/*
			if ( fieldIdx < 0 || fieldIdx > mNumFields ) {
				throw new OutOfBoundsException("fieldIdx out of bounds");
			}
*/

			return mysql_get_field_name(mResultHandle, fieldIdx);
		}

		public string getType(int fieldIdx) {
/*
			if ( fieldIdx < 0 || fieldIdx > mNumFields ) {
				throw new OutOfBoundsException("fieldIdx out of bounds");
			}
*/
			assertmsg(!"not implemented", "string getType(int fieldIdx) is not implemented");
		}

		public string getValue(int fieldIdx) {
/*
			if ( fieldIdx < 0 || fieldIdx > mNumFields ) {
				throw new OutOfBoundsException("fieldIdx out of bounds");
			}
*/

			return mysql_get_field_value(mResultHandle, fieldIdx);
		}

		public int numFields() const {
			return mNumFields;
		}

		public string toString() const {
			string result = "|";

			for ( int i = 0; i < mNumFields; i = i++ ) {
				Mysql.Entry e = getEntry(i);
				result = result + " " + e.name() + ": " + e.value() + " |";
			}

			return result;
		}
	}

}

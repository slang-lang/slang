
import Entry;
import Exceptions;
import System.Collections.List;

public namespace Mysql {

	public object Row {
		private System.List mEntries;
		private int mNumFields;
		private int mResultHandle;

		public void Constructor(int handle) {
			mEntries = new System.List();
			mResultHandle = handle;

			initialize();
		}

		public Mysql.Entry getEntry(int fieldIdx) {
/*
			if ( fieldIdx < 0 || fieldIdx > mNumFields ) {
				throw new OutOfBoundsException("fieldIdx out of bounds");
			}

			string name = mysql_get_field_name(mResultHandle, fieldIdx);
			string value = mysql_get_field_value(mResultHandle, fieldIdx);

			return new Mysql.Entry(name, value);
*/

			return Entry mEntries.at(fieldIdx);
		}

		public Mysql.Entry getEntry(string name) {
/*
			for ( int idx = 0; idx < mNumFields; idx = idx++ ) {
				if ( mysql_get_field_name(mResultHandle, idx) == name ) {
					return mysql_get_field_value(mResultHandle, idx);
				}
			}
*/

			for ( int idx = 0; idx < mEntries.size(); idx = idx++ ) {
				Entry e = Entry mEntries.at(idx);

				if ( e.name() == name ) {
					return e;
				}
			}

			return null;
		}

		public string getName(int fieldIdx) {
/*
			if ( fieldIdx < 0 || fieldIdx > mNumFields ) {
				throw new OutOfBoundsException("fieldIdx out of bounds");
			}

			return mysql_get_field_name(mResultHandle, fieldIdx);
*/

			Entry e = Entry mEntries.at(fieldIdx);
			return e.name();
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

			return mysql_get_field_value(mResultHandle, fieldIdx);
*/

			Entry e = Entry mEntires.at(fieldIdx);
			return e.value();
		}

		private void initialize() {
			mNumFields = mysql_num_fields(mResultHandle);

			for ( int fieldIdx = 0; fieldIdx < mNumFields; fieldIdx = fieldIdx++ ) {
				string name = mysql_get_field_name(mResultHandle, fieldIdx);
				string value = mysql_get_field_value(mResultHandle, fieldIdx);

				mEntries.push_back(Object new Entry(name, value));
			}
		}

		public int numFields() const {
			return mNumFields;
		}

		public string toString() const {
			string result = "|";

			for ( int i = 0; i < mNumFields; i = i++ ) {
				Entry e = Entry mEntries.at(i); //getEntry(i);
				result = result + " " + e.name() + ": " + e.value() + " |";
			}

			return result;
		}
	}

}

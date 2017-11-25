
import Entry;
import Exceptions;
import System.Collections.List;

public namespace Mysql {

	public object Row {
		private List mEntries;
		private int mNumFields;
		private int mResultHandle;

		public void Constructor(int handle) {
			mEntries = new List();
			mResultHandle = handle;

			initialize();
		}

		public Mysql.Entry getEntry(int fieldIdx) const{
			return Entry mEntries.at(fieldIdx);
		}

		public Mysql.Entry getEntry(string name) const {
			for ( int idx = 0; idx < mEntries.size(); idx = idx++ ) {
				Entry e = Entry mEntries.at(idx);

				if ( e.name() == name ) {
					return e;
				}
			}

			return Mysql.Entry null;
		}

		public string getName(int fieldIdx) const {
			Entry e = Entry mEntries.at(fieldIdx);
			return e.name();
		}

		public string getValue(int fieldIdx) const {
			Entry e = Entry mEntires.at(fieldIdx);
			return e.value();
		}

		private void initialize() modify {
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
				Entry e = Entry mEntries.at(i);
				result = result + " " + e.name() + ": " + e.value() + " |";
			}

			return result;
		}
	}

}

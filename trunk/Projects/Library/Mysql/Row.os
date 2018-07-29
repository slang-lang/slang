
// Library imports
import System.Collections.List;

// Project imports
import Entry;
import Exceptions;

public namespace Mysql { }

public object MysqlRow implements ICollection, IIterateable {
// Public

	public void Constructor(int handle) {
		mEntries = new List<MysqlEntry>();
		mHandle = handle;
		mNumFields = mysql_num_fields(handle);

		initialize();
	}

	public MysqlEntry at(int index) const throws {
		foreach ( MysqlEntry entry : mEntries ) {
			if ( entry == index ) {
				return entry;
			}
		}

		throw new MysqlException("no field with index('" + index + "')!");
	}

	public bool empty() const {
		return mNumFields == 0;
	}

	public MysqlEntry getEntry(string name) const throws {
		foreach ( MysqlEntry entry : mEntries ) {
			if ( entry == name ) {
				return entry;
			}
		}

		throw new MysqlException("no field with name('" + name + "')!");
	}

	public Iterator<MysqlEntry> getIterator() const {
		return new Iterator<MysqlEntry>(ICollection this);
	}

	public int numFields() const {
		return mNumFields;
	}

	public int size() const {
		return mNumFields;
	}

	public string toString() const {
		string result = "|";

		foreach ( MysqlEntry e : mEntries ) {
			result += " " + e.name() + ": " + e.value() + " |";
		}

		return result;
	}

// Private

	private void initialize() modify {
		for ( int fieldIdx = 0; fieldIdx < mNumFields; fieldIdx++ ) {
			mEntries.push_back(
				new MysqlEntry(
					fieldIdx,
					mysql_get_field_name(mHandle, fieldIdx),
					mysql_get_field_value(mHandle, fieldIdx)
				)
			);
		}
	}

	private List<MysqlEntry> mEntries;
	private int mHandle const;
	private int mNumFields const;
}


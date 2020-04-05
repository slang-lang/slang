
// Library imports

// Project imports

public namespace Mysql { }

public object MysqlSettings {
// Public

	public void Constructor() {
		mAutoEscaping = false;
	}

	public bool getAutoEscaping() const {
		return mAutoEscaping;
	}

	public void setAutoEscaping( bool state ) modify {
		mAutoEscaping = state;
	}

// Private
	private bool mAutoEscaping;
}


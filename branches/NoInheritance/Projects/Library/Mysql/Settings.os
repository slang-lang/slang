
public namespace Mysql {

	public object Settings {
		private bool mAutoEscaping;

		public void Constructor() {
			mAutoEscaping = false;
		}

		public string ToJsonString() const {
			return "{ "
			     + "mAutoEscaping: " + mAutoEscaping
			     + " }";
		}

		public string ToString() const {
			return "Settings={"
			     + "mAutoEscaping=" + mAutoEscaping + " "
			     + "}";
		}

		public bool getAutoEscaping() const {
			return mAutoEscaping;
		}

		public void setAutoEscaping(bool state) modify {
			mAutoEscaping = state;
		}
	}

}


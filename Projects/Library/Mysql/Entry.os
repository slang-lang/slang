
public namespace Mysql {

	public object Entry {
		private string mName;
		private string mValue;

		public void Entry() {
			mName = "null";
			mValue = "null";
		}

		public void Entry(string name, string value) {
			mName = name;
			mValue = value;
		}

		public void ~Entry() {
		}

		public string ToString() const {
			return "Entry={" +
					"mName=" + mName + ", " +
					"mValue=" + mValue + " " +
				"}";
		}

		public string name() const {
			return mName;
		}

		public string toString() const {
			return mName + ": " + mValue;
		}

		public string value() const {
			return mValue;
		}
	}

}


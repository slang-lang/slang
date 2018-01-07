
public namespace Mysql {

	public object Entry {
		private string mName;
		private string mValue;

		public void Constructor() {
			mName = "null";
			mValue = "null";
		}

		public void Constructor(string name, string value) {
			mName = name;
			mValue = value;
		}

		public string name() const {
			return mName;
		}

		public string value() const {
			return mValue;
		}
	}

}


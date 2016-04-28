
public namespace Mysql
{
	public object Entry
	{
		private string mName;
		private string mValue;

		public void Entry(string name, string value) {
			mName = name;
			mValue = value;
		}

		public void ~Entry() {
		}

		public string ToString() const {
			return mName + ": " + mValue;
		}

		public string name() const {
			return mName;
		}

		public string value() const {
			return mValue;
		}
	}
}


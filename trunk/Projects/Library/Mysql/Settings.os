
public namespace Mysql
{
	public object Settings
	{
		private bool mAutoEscaping;

		public void Settings()
		{
			mAutoEscaping = false;
		}

		public bool getAutoEscaping() const
		{
			return mAutoEscaping;
		}

		public void setAutoEscaping(bool state) modify
		{
			mAutoEscaping = state;
		}
	}
}


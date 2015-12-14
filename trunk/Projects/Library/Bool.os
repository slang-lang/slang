
public namespace
{
	public object Bool
	{
		private atomic_bool mValue;

		public void Bool(atomic_bool value = false) 
		{
			mValue = false;
		}

		public atomic_bool get() const
		{
			return mValue;
		}

		public void set(atomic_bool value)
		{
			mValue = value;
		}
	}
}

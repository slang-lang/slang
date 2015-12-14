
public namespace
{
	public object Number
	{
		private atomic_number mValue;

		public void Number(atomic_number value = 0)
		{
			mValue = value;
		}

		public void Number(atomic_number value)
		{
			mValue = value;
		}

		public atomic_number get() const
		{
			return mValue;
		}

		public void set(atomic_number n)
		{
			mValue = n;
		}

		public atomic_number operator_plus(atomic_number other)
		{
			return mValue + other;
		}
	}
}

public namespace Inheritance
{
	public interface IContainer
	{
		public String GetIdentifier() const;
	}

	public interface IWarehouse
	{
		public Number GetBox() const;
	}

	public object Base
	{
		public Number mPublicNumber;
		protected Number mProtectedNumber;
		private Number mPrivateNumber;

		public void Base()
		{
			mPublicNumber = 1;
			mProtectedNumber = 1;
			mPrivateNumber = 1;
		}

		public String ToString() const
		{
			return "mPublicNumber = " & mPublicNumber & ", mProtectedNumber = " & mProtectedNumber & ", mPrivateNumber = " & mPrivateNumber & ";";
		}
	}

	public object Main extends Base implements IContainer, IWarehouse
	{
		private Number mPrivateNumber;

		public void Main()
		{
			mPublicNumber = 2;
			mProtectedNumber = 2;
			mPrivateNumber = 2;
		}

		public Number GetBox() const
		{
			return Number(1);
		}

		public String GetIdentifier() const
		{
			return "bla";
		}

		public String ToString() const
		{
			return super.ToString() & "mPublicNumber = " & mPublicNumber & ", mProtectedNumber = " & mProtectedNumber & ", mPrivateNumber = " & mPrivateNumber & ";";
		}
	}
}


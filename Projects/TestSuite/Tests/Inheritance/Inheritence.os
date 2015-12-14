#!/usr/local/bin/oscript

public namespace Tests
{
	public namespace Inheritance
	{
		public interface IContainer
		{
			public string GetIdentifier() const;
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

			public string ToString() const
			{
				return "mPublicNumber = " & mPublicNumber & ", mProtectedNumber = " & mProtectedNumber & ", mPrivateNumber = " & mPrivateNumber & ";";
			}
		}

		public object Main extends public Base
						   implements public IContainer, public IWarehouse
		{
			private Number mPrivateNumber;

			public void Main(Number argc = 0, string argv = "")
			{
				test();
			}

			public Number GetBox() const
			{
				return Number(1);
			}

			public string GetIdentifier() const
			{
				return "bla";
			}

			public string ToString() const
			{
				return super.ToString() & "mPublicNumber = " & mPublicNumber & ", mProtectedNumber = " & mProtectedNumber & ", mPrivateNumber = " & mPrivateNumber & ";";
			}

			private void test()
			{
				mPublicNumber = 2;
				mProtectedNumber = 2;
				mPrivateNumber = 2;
			}
		}
	}
}

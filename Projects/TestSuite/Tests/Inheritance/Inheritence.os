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
			public number GetBox() const;
		}

		public object Base
		{
			public number mPublicNumber;
			protected number mProtectedNumber;
			private number mPrivateNumber;

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
			private number mPrivateNumber;

			public void Main(number argc = 0, string argv = "")
			{
				test();
			}

			public number GetBox() const
			{
				return number(1);
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

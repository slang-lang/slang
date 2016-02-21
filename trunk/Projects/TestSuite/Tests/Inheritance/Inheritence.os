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
			protected number mPublicNumber;	// public members are not allowed
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
				return "mPublicNumber = " + mPublicNumber + ", mProtectedNumber = " + mProtectedNumber + ", mPrivateNumber = " + mPrivateNumber + ";";
			}
		}

		public object Main extends Base, implements IContainer, IWarehouse
		{
			//private number mPrivateNumber;

			public void Main(number argc = 0, string argv = "")
			{
				print(ToString());
				//ToString2();

				test();

				print(ToString());
				//ToString2();
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
				return super.ToString() + "\nmPublicNumber = " + mPublicNumber + ", mProtectedNumber = " + mProtectedNumber + ", mPrivateNumber = " + mPrivateNumber + ";";
			}

			private void test() modify
			{
				mPublicNumber = 2;
				mProtectedNumber = 2;
				mPrivateNumber = 2;
			}
		}
	}
}

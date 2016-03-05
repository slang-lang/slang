#!/usr/local/bin/oscript

public namespace Inheritance
{
	public object BaseObject
	{
		protected number mPublicNumber;	// public members are not allowed, remember the "Law of Demeter"
		protected number mProtectedNumber;
		private number mPrivateNumber;

		public void BaseObject()
		{
			mPublicNumber = 1;
			mProtectedNumber = 1;
			mPrivateNumber = 1;
		}

		public string ToString() const
		{
			return "mPublicNumber = " + mPublicNumber + ", mProtectedNumber = " + mProtectedNumber + ", mPrivateNumber = " + mPrivateNumber;
		}
	}

	public object Main extends BaseObject
	{
		//private number mPrivateNumber;

		public void Main(number argc = 0, string argv = "")
		{
			base.BaseObject();

			print(ToString());
			print(ToString2());

			test();

			print(ToString());
			print(ToString2());
		}

		public number GetBox() const
		{
			return number(1);
		}

		public string GetIdentifier() const
		{
			return "bla";
		}

		public string ToString2() const
		{
			return base.ToString() + "	mPublicNumber = " + mPublicNumber + ", mProtectedNumber = " + mProtectedNumber + ", mPrivateNumber = " + mPrivateNumber;
		}

		private void test() modify
		{
			mPublicNumber = 2;
			mProtectedNumber = 2;
			mPrivateNumber = 2;
		}
	}
}

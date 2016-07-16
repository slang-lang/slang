#!/usr/local/bin/oscript

public namespace InstanciationTest
{
	public object OuterObject
	{
/*
		public object InnerObject
		{
			public string mValue;

			public void InnerObject(string value = "InnerObject")
			{
				mValue = value;
			}
		}
*/

		private string mValue;

		public void OuterObject(string value = "OuterObject")
		{
			mValue = value;
		}
	}
}

public object Main {
	public void Main(int arc = 0, string argv = "") {
		assert( TestCase1() );
	}

	private bool TestCase1() const {
		InstanciationTest.OuterObject outer = new InstanciationTest.OuterObject();
		print("outer.mValue = " + outer.mValue);

/*
		OuterObject.InnerObject inner = new InstanciationTest.OuterObject.InnerObject();
		print("inner.mValue = " + inner.mValue);
*/

		return true;
	}
}


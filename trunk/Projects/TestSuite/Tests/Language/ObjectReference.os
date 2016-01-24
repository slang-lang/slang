#!/usr/local/bin/oscript

public namespace Language
{
	public object TestObject
	{
		public number mValue;

		public void TestObject(number value)
		{
			mValue = value;
		}
	}

	public object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			assert( TestCase1() );
			//assert( TestCase2() );
			//assert( TestCase3() );
			assert( TestCase4() );
		}

		private bool TestCase1() const
		{
			print("TestCase1: parameter by value");

			TestObject obj = new TestObject(1);

			ParameterByValue(obj.mValue);

			return obj.mValue == 1;
		}

		private bool TestCase2() const
		{
			print("TestCase2: parameter as object by value");

			TestObject obj = new TestObject(1);

			ParameterByValue(obj);

			return obj.mValue == 1;
		}

		private bool TestCase3() const
		{
			print("TestCase3: parameter by reference");

			TestObject obj = new TestObject(1);

			ParameterByReference(obj.mValue);

			return obj.mValue == 2;
		}

		private bool TestCase4() const
		{
			print("TestCase4: parameter as object by reference");

			TestObject obj = new TestObject(1);

			ParameterByReference(obj);

			return obj.mValue == 2;
		}

		private void ParameterByReference(number value ref)
		{
			print("ParameterByReference(number): value = " + value);
			value = value + 1;
			print("ParameterByReference(number): value = " + value);
			assert(value == 2);
		}

		private void ParameterByReference(TestObject value ref)
		{
			print("ParameterByReference(TestObject): mValue = " + value.mValue);
			value.mValue = value.mValue + 1;
			print("ParameterByReference(TestObject): mValue = " + value.mValue);
			assert(value.mValue == 2);
		}

		private void ParameterByValue(number value val)
		{
			print("ParameterByValue(number): value = " + value);
			value = value + 1;
			print("ParameterByValue(number): value = " + value);
			assert(value == 2);
		}

		private void ParameterByValue(TestObject value const)
		{
			print("ParameterByValue(TestObject): mValue = " + value.mValue);
			value.mValue = value.mValue + 1;
			print("ParameterByValue(TestObject): mValue = " + value.mValue);
			assert(value.mValue == 2);
		}
	}


}

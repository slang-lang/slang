#!/usr/local/bin/oscript

public namespace Language
{
	public object TestObject
	{
		public number mValue;

		public void TestObject(number value = 1)
		{
			mValue = value;
		}
	}

	public object Main
	{
		private TestObject obj;

		public void Main(number argc = 0, string argv = "")
		{
			obj = new TestObject(1);	// instantiate new object (and execute it's constructor)
			print("value.mValue = " & obj.mValue);

			obj.mValue = 2;
			print("value.mValue = " & obj.mValue);

			ParameterByValue(obj.mValue);
			print("value.mValue = " & obj.mValue);

			//ParameterByReference(obj.mValue);
			print("value.mValue = " & obj.mValue);

			delete obj;					// delete object (and execute it's destructor)
		}

		private void ParameterByReference(TestObject value ref)
		{
			value.mValue = value.mValue + 1;
			print("mValue = " & value.mValue);
		}

		private void ParameterByReference(number value ref)
		{
			value = value + 1;
			print("ParameterByReference.value = " & value);
		}

		private void ParameterByValue(TestObject value val)
		{
			value.mValue = value.mValue + 1;
			print("mValue = " & value.mValue);
		}

		private void ParameterByValue(number value val)
		{
			value = value + 1;
			print("ParameterByValue.value = " & value);
		}
	}


}

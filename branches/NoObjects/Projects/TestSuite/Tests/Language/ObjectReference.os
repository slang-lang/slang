
public namespace {

	public object TestObject
	{
		public Number mValue;

		public void TestObject(Number value = 1)
		{
			mValue = value;
		}
	}

	public object Main
	{
		private TestObject obj;

		public void Main()
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

		private void ParameterByReference(Number value ref)
		{
			value = value + 1;
			print("ParameterByReference.value = " & value);
		}

		private void ParameterByValue(TestObject value val /*= TestObject(1)*/)
		{
			value.mValue = value.mValue + 1;
			print("mValue = " & value.mValue);
		}

		private void ParameterByValue(Number value val)
		{
			value = value + 1;
			print("ParameterByValue.value = " & value);
		}
	}


}

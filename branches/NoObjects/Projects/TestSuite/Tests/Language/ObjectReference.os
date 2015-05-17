
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
			DefaultParameter();

			// instantiate new object
			obj = new TestObject(1);

			obj.mValue = 2;
			print("value: " & obj.mValue);

			ParameterByValue(obj);
			print("value: " & obj.mValue);

			//ParameterByReference(obj);
			print("value: " & obj.mValue);

			// delete object (and execute it's destructor)
			delete obj;
		}

		private void ParameterByReference(TestObject value const ref)
		{
			value.mValue = value.mValue + 1;
			print("mValue = " & value.mValue);
		}

		private void ParameterByValue(TestObject value val = 0)
		{
			value.mValue = value.mValue + 1;
			print("mValue = " & value.mValue);
		}
		
		private void DefaultParameter(Number param = 1)
		{
			param = 2;
			print("param = " & param);
		}
	}


}

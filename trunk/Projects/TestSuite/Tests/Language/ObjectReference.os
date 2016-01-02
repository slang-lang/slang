#!/usr/local/bin/oscript

public namespace Language
{
	public object TestObject
	{
		public number mValue;

		public void TestObject(number value = 0)
		{
			mValue = value;
		}
	}

	public object Main
	{
		private TestObject obj;

		public void Main(number argc = 0, string argv = "")
		{
			obj = new TestObject();

			obj.mValue = 1;
			ParameterByValue(obj.mValue);
			print("obj.mValue = " + obj.mValue);
			assert( obj.mValue == 1 );
/*
			obj.mValue = 1;
			ParameterByValue(obj);
			print("obj.mValue = " + obj.mValue);
			assert( obj.mValue == 1 );
/*
			obj.mValue = 1;
			ParameterByReference(obj.mValue);
			print("obj.mValue = " + obj.mValue);
			assert( obj.mValue == 2 );
*/
			obj.mValue = 1;
			ParameterByReference(obj);
			print("obj.mValue = " + obj.mValue);
			assert( obj.mValue == 2 );

			delete obj;					// delete object (and execute it's destructor)
		}

		private void ParameterByReference(number value ref)
		{
			print("ParameterByReference(number): value = " + value);
			value = value + 1;
			print("ParameterByReference(number): value = " + value);
			assert(value == 2);
		}

		private void ParameterByReference(TestObject value const ref)
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

		private void ParameterByValue(TestObject value val)
		{
			print("ParameterByValue(TestObject): mValue = " + value.mValue);
			value.mValue = value.mValue + 1;
			print("ParameterByValue(TestObject): mValue = " + value.mValue);
			assert(value.mValue == 2);
		}
	}


}

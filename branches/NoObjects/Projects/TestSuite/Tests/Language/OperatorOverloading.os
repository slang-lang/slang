#!/usr/bin/oscript

public namespace OperatorOverloading
{
	private object UserObject
	{
		public Number mNumber;

		public void UserObject(Number one const)
		{
			mNumber = one;
			mNumber = 1;
		}

		public Number GetNumber() const
		{
			return mNumber;
		}

		public void operator_assign(Number other const)
		{
			print("operator_assign");
			assert(false);
			mNumber = other;
		}
		public void operator_divide(Number other const)
		{
			print("operator_divide");
			mNumber = mNumber / other;
		}
		public void operator_multiply(Number other const)
		{
			print("operator_multiply");
			mNumber = mNumber * other;
		}
		public void operator_plus(Number other const)
		{
			print("operator_plus");
			mNumber = mNumber + other;
		}
		public void operator_subtract(Number other const)
		{
			print("operator_subtract");
			mNumber = mNumber - other;
		}
	}

	public object Main
	{
		public void Main(Number argc const = 0, String argv const = "")
		{
			UserObject obj = new UserObject(1);
			obj = obj + 1;
			obj = obj - 1;
			obj = obj * 1;
			obj = obj / 1;

			print("obj.mNumber = " & obj.mNumber);
			print("obj.GetNumber() = " & obj.GetNumber());
		}
	}
}

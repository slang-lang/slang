#!/usr/local/bin/oscript

public namespace ConstCorrectness1
{
	public object Main
	{
		private number mNumber;

		public void Main(number argc const = 0, string argv const = "")
		{
			mNumber = 0;
			number one = 0;
			ModifyByValueParameter(one);
			assert( mNumber == 1 );
			assert( one == 0 );

			mNumber = 0;
			one = 0;
			ModifyByReferenceParameter(one);	// this is not supported atm
			assert( mNumber == 1 );
			//assert( one == 1 );				// atomic reference parameters are not supported atm

			mNumber = 0;
			number two const = 0;
			ModifyConstParameter(two);
			assert( false );
			assert( mNumber == 2 );
			assert( one == 0 );

			mNumber = 0;
			number three = 0;
			ModifyMemberInConstMethod(three);
			assert( false );
			assert( mNumber == 0 );
			assert( three == 0 );
		}

		private void ModifyByReferenceParameter(number value ref) modify
		{
			mNumber = 1;	// valid
			value = 1;		// valid
		}

		private void ModifyByValueParameter(number value val) modify
		{
			mNumber = 1;	// valid
			value = 1;		// valid, but argh...
		}

		private void ModifyConstParameter(number value const) modify
		{
			mNumber = 2;	// valid
			value = 2;		// invalid, throws a ConstCorrectnessViolated exception
			
			assert( false );
		}

		private void ModifyMemberInConstMethod(number value const) const
		{
			mNumber = value;	// invalid, throws a ConstCorrectnessViolated exception
			value = 2;			// invalid, throws a ConstCorrectnessViolated exception
			
			assert( false );
		}
	}
}

#!/usr/local/bin/oscript

public namespace ExceptionTest {
	private object Exception {
		private string _exception;

		private void Constructor(string ex) {
			print(ex);
			_exception = ex;
		}

		public string what() const {
			return "Exception: " + _exception;
		}
	}

	private object ObjectThatThrows {
		public void ObjectThatThrows() {
			// not implementing this constructor and using the default constructor would also be valid
		}

		public void MethodThatThrows() throws {
			throw new ExceptionTest.Exception("MethodThatThrows()");
		}
	}
}

public void Main(int argc = 0, string argv = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
	assert( TestCase5() );
	assert( TestCase6() );
	assert( TestCase7() );
}

private bool TestCase1() throws {
	print("TestCase 1");

	try {
		print("try");

		int one = 1;
		print("one = " + one);

		throw;

		assert( false );
	}

	return true;
}

private bool TestCase2() throws {
	print("TestCase 2");

	try {
		int one = 1;
		print("one = " + one);

		throw;

		assert( false );
	}
	finally {
		int one = 2;
		print("one = " + one);
	}

	return true;
}

private bool TestCase3() throws {
	print("TestCase 3");

	try {
		int one = 1;
		print("one = " + one);

		throw;

		assert( false );
	}
	catch {
		int one = 2;
		print("one = " + one);
	}
	finally {
		int one = 3;
		print("one = " + one);
	}
	return true;
}

private bool TestCase4() throws {
	print("TestCase 4");

	ExceptionTest.ObjectThatThrows obj = new ExceptionTest.ObjectThatThrows();

	try {
		print("try");

		obj.MethodThatThrows();

		assert( false );
	}
	catch {
		print("catch");
	}
	finally {
		print("finally");
	}

	return true;
}

private bool TestCase5() throws {
	print("TestCase 5");

	try {
		print("outter try");

		try {
			print("inner try");

			throw;

			assert( false );
		}
		catch {
			print("inner catch");
		}
		finally {
			print("inner finally");
		}
	}
	catch {
		print("outter catch");
		assert(false);
	}
	finally {
		print("outter finally");
	}

	return true;
}

private bool TestCase6() throws {
	print("TestCase 6");

	try {
		print("try");

		print("throw new Exception()");
		throw new ExceptionTest.Exception("standard exception");
	}
	catch ( int e ) {
		print("FAIL!!!");
		return false;
	}
	catch ( ExceptionTest.Exception e ) {
		print("catch " + e.what());
	}
	catch ( Object e ) {
		print("caugth generic exception type: " + e.what());
	}
	finally {
		print("finally");
	}

	return true;
}

private bool TestCase7() throws {
	print("TestCase 7: throw without matching catch");

	try {
		try {
			print("try");

			print("throw new ExceptionTest.Exception");
			throw new ExceptionTest.Exception("ExceptionTest.Exception");
		}
		catch ( int e ) {
			assert(false);
		}

		print("after catch");

		return false;
	}
	catch ( ExceptionTest.Exception e ) {
		print("correct catch: " + e.what());

		return true;
	}

	return false;
}

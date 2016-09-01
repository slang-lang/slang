
public namespace System {

	public object Exception {
		private string _exception;

		public void Exception(string ex) {
			_exception = ex;
		}

		public string what() const {
			return _exception;
		}
	}

	public object NullPointerException extends Exception {
		public void NullPointerException(string ex) {
			base.Exception("NullPointerException: " + ex);
		}
	}

	public object OutOfBoundsException extends Exception {
		public void OutOfBoundsException(string ex) {
			base.Exception("OutOfBoundsException: " + ex);
		}
	}

	public object SecurityException extends Exception {
		public void SecurityException(string ex) {
			base.Exception("SecurityException: " + ex);
		}
	}

}


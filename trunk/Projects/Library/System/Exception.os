
public namespace System {

	public object Exception {
		private string _exception;

		public void Exception(string ex const) {
			_exception = ex;
		}

		public string what() const {
			return _exception;
		}
	}

	public object NullPointerException replicates Exception;
	public object OutOfBoundsException replicates Exception;
	public object SecurityEcxeption replicates Exception;

}


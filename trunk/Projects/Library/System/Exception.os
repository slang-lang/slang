
public namespace System {

	public interface IException {
		public string what() const;
	}

	public object Exception /*implements IException*/ {
		private string _exception;

		public void Exception(string ex const) {
			_exception = ex;
		}

		public string what() const {
			return _exception;
		}
	}

	public object OutOfBoundsException replicates Exception;

}


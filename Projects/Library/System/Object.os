
public namespace System {

	public interface IObject {
		public string GetObjectType() const;
		public string ToString() const;
	}

	public object TObject implements IObject {

		/*
		 * Returns a JSON-formatted string
		 */
		public string ToJsonString() const {
			return "{ }";
		}

	}

}


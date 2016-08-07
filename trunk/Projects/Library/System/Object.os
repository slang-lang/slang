
// declare 'System' namespace to prevent a user defined private 'System' namespace
public namespace System { }

public interface IObject {
	public string GetObjectType() const;
	public string ToJsonString() const;
	public string ToString() const;
}

public object TObject implements IObject {

	public string GetObjectType() const {
		return "TObject";
	}

	/*
	 * Returns a JSON-formatted string
	 */
	public string ToJsonString() const {
		return "{ }";
	}

	public string ToString() const {
		return "";
	}

}


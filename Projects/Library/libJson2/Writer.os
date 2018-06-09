
import Array;
import Exceptions;
import Object;


public namespace Json {

public object Writer {
	public string toString(Json.Value value ref) const throws {
		if ( !value ) {
			throw new Exception("invalid Json Value provided!");
		}

		if ( value is Array ) {
			return toString(Array value);
		}
		else if ( value is Object ) {
			return toString(Object value);
		}

		return value.getKey() + ": " + value.toString();
	}

	private string toString(Json.Array value ref) const {
		return value.toString();
	}

	private string toString(Json.Object value ref) const {
		return value.toString();
	}
}

}


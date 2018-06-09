
// Library imports
import System.Collections.Vector;

// Project imports
import Value;


public namespace Json {

public object Array extends Json.Value {
	private Vector<Value> mValues;

	public void Constructor() {
		mType = Value.Type.Array;
		mValues = new Vector<Value>();
	}
}

}


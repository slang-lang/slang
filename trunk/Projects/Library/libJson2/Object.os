
import Value;

public namespace Json {

public object Object extends Json.Value {
	public void Constructor() {
		base.Constructor();

		mType = Value.Type.Object;
	}
}

}



import CircularExtendedObject;

public object CircularBaseObject {
	private InnerObject mInner;

	public void Constructor() {
		writeln("Constructor(): Start");

		mInner = new InnerObject();

		writeln("Constructor(): End");
	}

	public void Destructor() {
		writeln("Destructor(): Start");

		writeln("Destructor(): End");
	}

	public string ToString() const {
		return "ToString(): CircularBaseObject";
	}
}


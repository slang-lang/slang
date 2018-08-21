
import CircularExtendedObject;

public object CircularBaseObject {
	private InnerObject mInner;

	public void Constructor() {
		writeln("CircularBaseObject.Constructor()");

		mInner = new InnerObject();
	}

	public void Destructor() {
		delete mInner;

		writeln("CircularBaseObject.Destructor()");
	}

	public string ToString() const {
		return "ToString(): CircularBaseObject";
	}
}



import CircularBaseObject;

public object InnerObject {
	public void Constructor() {
		writeln("Constructor(): Start");

		writeln("Constructor(): End");
	}

	public void Destructor() {
		writeln("Destructor(): Start");

		writeln("Destructor(): End");
	}

	public string ToString() const {
		return "ToString(): InnerObject";
	}
}

public object CircularExtendedObject extends CircularBaseObject {
	//private InnerObject mInner;

	public void Constructor() {
		writeln("Constructor(): Start");

		//mInner = new InnerObject();

		writeln("Constructor(): End");
	}

	public void Destructor() {
		writeln("Destructor(): Start");

		writeln("Destructor(): End");
	}

	public string ToString() const {
		return "ToString(): CircularExtendedObject extends " + base.ToString();
	}
}


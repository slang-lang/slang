
import CircularBaseObject;

public object InnerObject {
	public void Constructor() {
		writeln("InnerObject.Constructor()");
	}

	public void Destructor() {
		writeln("InnerObject.Destructor()");
	}

	public string ToString() const {
		return "ToString(): InnerObject";
	}
}

public object CircularExtendedObject extends CircularBaseObject {
	public void Constructor() {
		writeln("CircularExtendedObject.Constructor()");

		base.Constructor();
	}

	public void Destructor() {
		base.Destructor();

		writeln("CircularExtendedObject.Destructor()");
	}

	public string ToString() const {
		return "ToString(): CircularExtendedObject extends " + base.ToString();
	}
}


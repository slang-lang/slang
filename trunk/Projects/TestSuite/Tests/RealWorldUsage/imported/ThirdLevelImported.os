
import DerivedObjectImported;

public object ThirdLevelImported extends DerivedObjectImported {
	public void Constructor() {
		print("Constructor()");
	}

	public void Destructor() {
		print("Destructor()");
	}

	public string ToString() const {
		return "ThirdLevelImported extends " + base.ToString();
	}
}


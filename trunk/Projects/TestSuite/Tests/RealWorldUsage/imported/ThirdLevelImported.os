
import DerivedObjectImported;

public object ThirdLevelImported extends DerivedObjectImported {
	public void Constructor() {
		print("ThirdLevelImported.Constructor()");
	}

	public void Destructor() {
		print("ThirdLevelImported.Destructor()");
	}

	public string ToString() const {
		return "ThirdLevelImported extends " + base.ToString();
	}
}



import System.Object;

public object IObjectImplementation implements /*System.*/IObject {
	public void IObjectImplementation() {
	}
	
	public string GetObjectType() const {
		return "IObjectImplementation";
	}
	
	public string ToString() const {
		return "IObjectImplementation.ToString()";
	}
}

public object Main {
	public void Main(int argc, string args) {
		assert( TestCase1() );
		assert( TestCase2() );
	}

	public bool TestCase1() const {
		IObjectImplementation obj = new IObjectImplementation();

		print(obj.ToString());

		return obj;
	}

	public bool TestCase2() const {
		TObject obj = new TObject();

		print(obj.ToString());

		return obj;
	}
}

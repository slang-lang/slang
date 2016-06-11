
import CircularBaseObject;

public object InnerObject
{
	public void InnerObject() {
		writeln("InnerObject(): Start");

		writeln("InnerObject(): End");
	}

	public void ~InnerObject() {
		writeln("~InnerObject(): Start");

		writeln("~InnerObject(): End");
	}

	public string ToString() const {
		return "ToString(): InnerObject";
	}
}

public object CircularExtendedObject extends CircularBaseObject
{
	//private InnerObject mInner;

	public void CircularExtendedObject()
	{
		writeln("CircularExtendedObject(): Start");

		//mInner = new InnerObject();

		writeln("CircularExtendedObject(): End");
	}

	public void ~CircularExtendedObject()
	{
		writeln("~CircularExtendedObject(): Start");

		writeln("~CircularExtendedObject(): End");
	}

	public string ToString() const
	{
		return "ToString(): CircularExtendedObject extends " + base.ToString();
	}
}


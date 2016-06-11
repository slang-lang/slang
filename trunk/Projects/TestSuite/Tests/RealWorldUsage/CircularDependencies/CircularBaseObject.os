
import CircularExtendedObject;

public object CircularBaseObject
{
	private InnerObject mInner;

	public void CircularBaseObject()
	{
		writeln("CircularBaseObject(): Start");

		mInner = new InnerObject();

		writeln("CircularBaseObject(): End");
	}

	public void ~CircularBaseObject()
	{
		writeln("~CircularBaseObject(): Start");

		writeln("~CircularBaseObject(): End");
	}

	public string ToString() const
	{
		return "ToString(): CircularBaseObject";
	}
}


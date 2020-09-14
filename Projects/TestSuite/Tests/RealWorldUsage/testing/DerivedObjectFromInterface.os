#!/usr/local/bin/slang

public interface IBaseInterface {
	public void Method();
}

public object DerivedObject implements IBaseInterface {
	public override void Method() { }
}

public void Main( int argc, string args ) {
}


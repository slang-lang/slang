#!/usr/local/bin/slang

public interface IBaseInterface {
	public void Method();
}

public interface IDerivedInterface implements IBaseInterface {
	public void Method();
}

public void Main( int argc, string args ) {
}


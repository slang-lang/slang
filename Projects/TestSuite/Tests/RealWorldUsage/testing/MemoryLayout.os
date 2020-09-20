#!/usr/local/bin/slang

public object TestObject {
	// ABSTRACT
	// {
	public abstract void MethodAbstract();

	//public void MethodAbstract() abstract;
	// }

	// FINAL
	// {
	public final void MethodFinal() { }

	//public void MethodFinal() final { }
	// }

	// OVERRIDE
	// {
	public override void MethodOverride() { }

	//public void MethodOverride() override { }
	// }

	// STATIC
	// {
	public static void MethodStatic() { }
	// }

	// VIRTUAL
	// {
	public virtual void MethodVirtual() { }

	//public void MethodVirtual() virtual { }
	// }

	public abstract int mAbstract;
	public final int mFinal;
	public override int mOverride;
	public static int mStatic;
	public virtual int mVirtual;
}

public void Main( int argc, string args ) {
}


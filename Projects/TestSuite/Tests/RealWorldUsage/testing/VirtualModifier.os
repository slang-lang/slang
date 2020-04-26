#!/usr/local/bin/slang

public object VirtualModifierObject {
	public abstract void PrintAbstract();

	public final void PrintFinal() {
		print("VirtualModifierObject.PrintFinal");
	}

	public virtual void PrintVirtual() {
		print("VirtualModifierObject.PrintVirtual");
	}
}

public object DerivedObject extends VirtualModifierObject {
	public void PrintAbstract() {
		print("DerivedObject.PrintAbstract");
	}

	public void PrintFinal() {
		print("DerivedObject.PrintFinal");
	}

	public void PrintVirtual() {
		print("DerivedObject.PrintVirtual");
	}
}

public void Main(int argc, string args) {
	VirtualModifierObject obj = VirtualModifierObject new DerivedObject();

	obj.PrintAbstract();
	obj.PrintFinal();
	obj.PrintVirtual();
}


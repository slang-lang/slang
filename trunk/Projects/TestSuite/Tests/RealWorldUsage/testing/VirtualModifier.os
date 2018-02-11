#!/usr/local/bin/oscript

public object VirtualModifierObject {
	public void PrintAbstract() abstract;

	public void PrintFinal() final {
		print("VirtualModifierObject.PrintFinal");
	}

	public void PrintVirtual() virtual {
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
}

public void Main(int argc, string args) {
	VirtualModifierObject obj = new DerivedObject();

	obj.PrintAbstract();
	obj.PrintFinal();
	obj.PrintVirtual();
}


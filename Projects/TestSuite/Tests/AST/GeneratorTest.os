#!/usr/local/bin/slang

private namespace Space {
	public void NamespacedMethod() {
		print("NamespacedMethod()");
	}
}

public void Main(int argc = 0, string args = "") {
	print("Main(" + argc + ", " + args + ")");

	methodCall();

	Space.NamespacedMethod();

	print("end.");
}

private void methodCall() {
	print("methodCall()");
}


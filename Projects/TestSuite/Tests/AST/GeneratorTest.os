#!/usr/local/bin/oscript

private namespace Space {
	public void NamespacedMethod() {
		print("NamespacedMethod()");
	}
}

public void Main(int argc = 0, string args = "") {

	print("Main()");

	methodCall();

	Space.NamespacedMethod();

	print("end.");

}

private void methodCall() {
	print("methodCall()");
}


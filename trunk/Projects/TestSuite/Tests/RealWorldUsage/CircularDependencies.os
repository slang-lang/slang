#!/usr/local/bin/oscript

import CircularDependencies.CircularBaseObject;
import CircularDependencies.CircularExtendedObject;

public void Main(int argc, string argv) {
	CircularBaseObject baseObject = new CircularBaseObject();

	writeln(baseObject.ToString());
	writeln("");

	CircularExtendedObject extendedObject = new CircularExtendedObject();

	writeln(extendedObject.ToString());
	writeln("");
}


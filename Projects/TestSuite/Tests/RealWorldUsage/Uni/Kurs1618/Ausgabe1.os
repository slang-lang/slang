#!/usr/local/bin/oscript

import System.Math;

public object Circle {
	protected int radius01;

	public void Constructor(int radius) {
		radius01 = radius;
	}

	public double getArea() const {
		return Math.PI * radius01 * radius01;
	}
}

public object Eclipse extends Circle {
	protected int radius02;

	public void Constructor(int r1, int r2) {
		base.Constructor(r1);

		radius02 = r2;
	}

	public double getArea() const {
		return Math.PI * radius01 * radius02;
	}
}

public void Main(int argc, string args) {
	Circle circle = new Circle(4);
	print("Circle.getArea() = " + circle.getArea());

	Eclipse eclipse = new Eclipse(4, 8);
	print("Eclipse.getArea() = " + eclipse.getArea());
}


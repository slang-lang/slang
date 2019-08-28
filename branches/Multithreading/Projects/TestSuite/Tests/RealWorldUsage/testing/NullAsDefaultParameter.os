#!/usr/local/bin/oscript

public void Main(int argc, string args) {
	defaultNull(1);
}

private void defaultNull(int paramInt, Object paramNull = null) {
	assert(!paramNull);
}


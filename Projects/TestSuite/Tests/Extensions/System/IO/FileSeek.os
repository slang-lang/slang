#!/usr/local/bin/oscript

public void Main(int argc, string argv) {
	int file = 0;
	int result = 0;

	try {
		file = fopen("file.complex", "r");
		print("handle = " + file);

		result = fseek(file, 1);
		print("result = " + result);

		double doubleValue = freadd(file);
		print("doubleValue = " + doubleValue);

		result = fseek(file, 9);
		print("result = " + result);

		float floatValue = freadf(file);
		print("floatValue = " + floatValue);

		result = fseek(file, 13);
		print("result = " + result);

		string stringValue = freads(file, 7);
		print("stringValue = " + stringValue);

		result = fclose(file);
		print("result = " + result);
	}
	catch {
		print("error while seeking");
	}
}


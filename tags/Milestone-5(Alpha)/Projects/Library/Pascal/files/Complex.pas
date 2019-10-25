PROGRAM Complex;
VAR
	number: INTEGER := 2;
	a: INTEGER;
	b: INTEGER;
	c: INTEGER;
	x: INTEGER := 11;
BEGIN
	BEGIN
		a := number;
		b := 10 * a + 10 * number / 4;
		c := a - -b;

		WRITELN( c );
	END;

	WRITELN( x );
END.

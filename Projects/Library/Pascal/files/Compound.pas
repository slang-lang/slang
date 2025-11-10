PROGRAM Compound;
VAR
	A: INTEGER := 1;
	B: INTEGER;
BEGIN
	CONST C: STRING := 'bla';
	BEGIN
		B := 2;
		WRITELN( 'B + C = ' + B + C );
	END;

	VAR D: INTEGER;
	BEGIN
		D := 1;
		WRITELN( 'D = ' + D );
	END;

	BEGIN
		WRITELN( 'No decl' );
	END;
END.

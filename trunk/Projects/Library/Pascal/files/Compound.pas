PROGRAM Compound;
VAR
	A: INTEGER := 1;
	B: INTEGER;
BEGIN
	CONST C: STRING := 'bla';
	BEGIN
		B := 2;
		PRINT( 'B + C = ' + B + C );
	END;

	VAR D: INTEGER;
	BEGIN
		D := 1;
		PRINT( 'D = ' + D );
	END;

	BEGIN
		PRINT( 'No decl' );
	END;
END.

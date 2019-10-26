PROGRAM WhileBreak;
VAR A: INTEGER;
BEGIN
	A := 10;

	WHILE ( A > 0 ) DO
	BEGIN
		WRITELN( A );

		A := A - 1;

		BREAK;
	END;

	WHILE ( A < 10 ) DO
		A := A + 1;

	WRITELN( 'A = ' + A );
END.

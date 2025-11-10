PROGRAM WhileExit;
VAR A: INTEGER;
BEGIN
	A := 10;

	WHILE ( A > 0 ) DO
	BEGIN
		WRITELN( A );

		EXIT;

		A := A - 1;
	END;

	WHILE ( A < 10 ) DO
		A := A + 1;

	WRITELN( 'A = ' + A );
END.

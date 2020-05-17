PROGRAM WhileTest;
VAR
	A: INTEGER;
BEGIN
	A := 10;

	WRITELN( 'A(1) = ' + A );

	WHILE ( A > 0 ) DO
	BEGIN
		WRITELN( 'A = ' + A );

		A := A - 1;
	END;

{
	WHILE ( A > 0 ) DO
		A := A - 1;
}

	WRITELN( 'A(2) = ' + A );

	WHILE ( A < 10 ) DO
		A := A + 1;

	WRITELN( 'A(3) = ' + A );
END.

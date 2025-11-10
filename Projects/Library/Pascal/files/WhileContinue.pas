PROGRAM WhileContinue;
VAR A: INTEGER;
BEGIN
	A := 10;

	WHILE ( A > 0 ) DO
	BEGIN
		WRITELN('before continue');

		A := A - 1;

		CONTINUE;

		WRITELN('after continue');
	END;

	WHILE ( A < 10 ) DO
		A := A + 1;

	WRITELN( 'A = ' + A );
END.

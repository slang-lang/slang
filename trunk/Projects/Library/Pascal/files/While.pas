PROGRAM WhileTest;
VAR A: INTEGER;
BEGIN
	A := 10;

	WHILE ( A > 0 ) DO
	BEGIN
		PRINT( A );

		A := A - 1;
	END;
END.

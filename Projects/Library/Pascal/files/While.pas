PROGRAM WhileTest;
BEGIN
	VAR A := 10;

	WHILE ( A > 0 )
	BEGIN
		PRINT( A );

		A := A - 1;
	END;
END.

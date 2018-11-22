PROGRAM IfStatement;
BEGIN
	A := 0;

	IF A = 1 THEN BEGIN
		PRINT( 'A = 1' );
	END
	ELSE IF A = 2 THEN BEGIN
		PRINT( 'A = 2' );
	END
	ELSE BEGIN
		PRINT( 'A <> [1,2]' );
	END;
END.

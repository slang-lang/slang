PROGRAM IfStatement;
VAR A: BOOLEAN;
BEGIN
	A := 0 OR 1;
	WRITELN( A );

	IF A < 1 THEN BEGIN
		WRITELN( 'A < 1' );
	END
	ELSE IF A = 1 THEN BEGIN
		WRITELN( 'A = 1' );
	END
	ELSE IF A = 2 THEN BEGIN
		WRITELN( 'A = 2' );
	END
	ELSE IF A > 2 THEN BEGIN
		WRITELN( 'A > 2' );
	END;

	A := 5;
	IF ( A = 1 ) OR ( A = 2 ) THEN
		WRITELN( 'A = (1|2)' )
	ELSE
		WRITELN( 'A > 2' );
END.

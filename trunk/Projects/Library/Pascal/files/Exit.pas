PROGRAM FunctionTest;

	FUNCTION GETSTRING: STRING;
	BEGIN
		Result := 'bla';
		EXIT;

		WriteLn( 'This should not be printed...' );
	END;

BEGIN
	WRITELN( 'FunctionTest' );

	WRITELN( GETSTRING + ' vs ' + GETSTRING );

	WRITELN( 'Another try' );

	WRITELN( GETSTRING + ' vs ' + GETSTRING );
END.

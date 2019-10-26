PROGRAM FunctionTest;

	FUNCTION GETSTRING: STRING;
	BEGIN
		Result := 'bla';
	END;

BEGIN
	WRITELN( 'FunctionTest' );

	WRITELN( GETSTRING + ' vs ' + GETSTRING );
END.

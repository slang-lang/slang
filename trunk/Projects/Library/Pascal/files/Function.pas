PROGRAM FunctionTest;

	FUNCTION GETSTRING: STRING;
	BEGIN
		Result := 'bla';
	END;

BEGIN
	PRINT( 'FunctionTest' );

	PRINT( GETSTRING + ' vs ' + GETSTRING );
END.

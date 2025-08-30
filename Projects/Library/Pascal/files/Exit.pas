PROGRAM FunctionTest;

	FUNCTION GETSTRING: STRING;
	BEGIN
		Result := 'bla';
		EXIT( 'exit' );

		WriteLn( 'This should not be printed...' );
	END;

	PROCEDURE RETURNVALUE;
	BEGIN
		WRITELN( 'Return value' );

		BREAK;

		{EXIT( '10' );}
		EXIT;
	END;

BEGIN
	WRITELN( 'FunctionTest' );

	WRITELN( GETSTRING + ' vs ' + GETSTRING );

	WRITELN( 'Another try' );

	WRITELN( GETSTRING + ' vs ' + GETSTRING );

	RETURNVALUE;
END.

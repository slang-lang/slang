PROGRAM FunctionTestWithParameter;

	FUNCTION GETSTRING(param1: STRING): STRING;
	BEGIN
		Result := param1;
	END;

BEGIN
	WRITELN( 'Function test with parameter' );

	WRITELN( 'GETSTRING = ' + GETSTRING('param1') );
END.

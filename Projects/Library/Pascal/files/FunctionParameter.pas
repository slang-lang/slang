PROGRAM FunctionTestWithParameter;

	FUNCTION GETSTRING(param1: STRING): STRING;
	BEGIN
		Result := param1;
	END;

BEGIN
	PRINT( 'Function test with parameter' );

	PRINT( 'GETSTRING = ' + GETSTRING('param1') );
END.

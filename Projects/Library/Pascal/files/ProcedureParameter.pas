PROGRAM ProcedureTestWithParameter;

	PROCEDURE PROC;
	BEGIN
	END;

	PROCEDURE YELL(param: STRING);
	BEGIN
		PRINT( 'Hello World, ' + param );
	END;

BEGIN
	PRINT( 'Procedure test with parameter' );

	YELL('param 1');

	PROC;
END.

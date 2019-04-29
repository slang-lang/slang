PROGRAM ProcedureTestWithParameter;

	PROCEDURE PROC;
	BEGIN
	END;

	PROCEDURE YELL(param: STRING);
	BEGIN
		WRITELN( 'Hello World, ' + param );
	END;

BEGIN
	WRITELN( 'Procedure test with parameter' );

	YELL('param 1');

	PROC;
END.

PROGRAM Procedure_Test;

	PROCEDURE YELL;
	VAR
		count: Integer := 0;
	BEGIN
		PRINT( 'Hello World!' );
	END;

	PROCEDURE BLA;
	VAR
		count: Integer := 1;
	BEGIN
		WHILE ( count <= 10 ) DO
		BEGIN
			PRINT( 'count: ' + count );
			count := count + 1;
		END;

		YELL;
	END;

BEGIN
	PRINT( 'ProcedureTest' );

	YELL;

	BLA;
END.
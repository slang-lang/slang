PROGRAM Procedure_Test;

	PROCEDURE YELL;
	BEGIN
		WRITELN( 'Hello World!' );
	END;

	PROCEDURE BLA;
	VAR
		count: Integer := 1;
	BEGIN
		WHILE ( count <= 10 ) DO
		BEGIN
			WRITELN( 'count: ' + count );
			count := count + 1;
		END;

		YELL;
	END;

BEGIN
	WRITELN( 'ProcedureTest' );

	YELL;

	BLA;
END.

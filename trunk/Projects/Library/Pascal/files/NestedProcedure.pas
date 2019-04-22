PROGRAM Nested_Procedure_Test;

	PROCEDURE Level1;
	VAR
		level: String := 'Level 1';
		x1: Integer := 1;

		PROCEDURE Level2;
		VAR
			level: String := 'Level 2';
			x2: Integer := 2;
		BEGIN
			PRINT( 'level: "' + level + '", x2: ' + x2 );
		END;

	BEGIN
		PRINT( 'level: "' + level + '", x1: ' + x1 );

		Level2;

		PRINT( 'level: "' + level + '", x1: ' + x1 );
	END;

BEGIN
	PRINT( 'NestedProcedureTest' );

	Level1;
END.

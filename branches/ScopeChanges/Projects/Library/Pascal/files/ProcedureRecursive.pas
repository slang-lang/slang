PROGRAM ProcedureRecursive;

PROCEDURE Recursive(count: Integer);
BEGIN
	WRITELN('Recursive calls: ' + count);

	IF count < 10 THEN BEGIN
		Recursive(count + 1);
	END;
END;

BEGIN
	Recursive(1);
END.


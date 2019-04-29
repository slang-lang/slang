PROGRAM FunctionRecursive;

FUNCTION Recursive(count: Integer): Integer;
BEGIN
	PRINT( 'Count: ' + count );

	IF count < 10 THEN
		Result := Recursive(count + 1)
	ELSE
		Result := count;
END;

BEGIN
	PRINT( 'Recursive: ' + Recursive(1) );
END.


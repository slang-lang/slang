PROGRAM FunctionRecursive;

FUNCTION Recursive(count: Integer): Integer;
BEGIN
	WRITELN( 'Count: ' + count );

	IF count < 10 THEN
		Result := Recursive(count + 1)
	ELSE
		Result := count;
END;

BEGIN
	WRITELN( 'Recursive: ' + Recursive(1) );
END.


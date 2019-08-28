program CaseTest;
var idx: Integer := 2;
begin
	WriteLn( 'Case test' );

	case idx of
		1,2,3: WriteLn( 'idx = 1 OR 2 OR 3' );
		173  : WriteLn( 'idx = 173' );
		else WriteLn( 'else' );
	end;

	WriteLn( 'Done.' );
end.

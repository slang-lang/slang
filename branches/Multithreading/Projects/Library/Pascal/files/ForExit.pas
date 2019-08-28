Program ForExit;
Var
	idx: Integer;
Begin
	Writeln( 'For Test' );

	for idx := 1 to 10 do
	begin
		WriteLn( idx );
		Exit;
	end;

	Writeln( 'Done.' );
End.

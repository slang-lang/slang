Program ForContinue;
Var
	idx: Integer;
Begin
	Writeln( 'For Test' );

	for idx := 1 to 10 do
	begin
		WriteLn( idx );
		continue;
		WriteLn( idx );
	end;

	Writeln( 'Done.' );
End.

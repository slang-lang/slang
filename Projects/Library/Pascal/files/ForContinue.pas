Program ForContinue;
Var
	idx: Integer;
Begin
	Writeln( 'For Test' );

	for idx := 1 to 10 do
	begin
		WriteLn( 'before continue' );
		continue;
		WriteLn( 'after continue' );
	end;

	Writeln( 'Done.' );
End.

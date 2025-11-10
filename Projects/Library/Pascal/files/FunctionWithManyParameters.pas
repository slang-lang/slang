Program FunctionWithManyParameters;

Function Func1(param1: string; param2: integer; param3: boolean): string;
Begin
	Result := param1 + param2 + param3;
End;

Begin
	Writeln( Func1('bla', 17, false) );
End.

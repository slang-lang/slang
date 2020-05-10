program Main;
var
   x : real := 1;
   y : real := 2;
   z : integer := 3;

   function AlphaA(a : integer): integer;
   var y : integer := 5;
   begin { AlphaA }
      writeln( 'AlphaA(' + a + ')' );

      x := a + x + y;

      writeln( 'x = ' + x );
   end;  { AlphaA }

   function AlphaB(a : integer): integer;
   var b : integer;
   begin { AlphaB }
      writeln( 'AlphaB(' + a + ')' );

      AlphaA(a);

      writeln( 'b = ' + b );
   end;  { AlphaB }

begin { Main }
   writeln( 'Nested functions' );

   writeln( 'x = ' + x );

   AlphaB(1);
end.  { Main }


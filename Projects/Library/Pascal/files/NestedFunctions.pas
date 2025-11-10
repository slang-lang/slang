program Main;
var
   x : real;
   y : real;
   z : integer;

   function AlphaA(a : integer): integer;
   var y : integer;
   begin { AlphaA }
      writeln( 'AlphaA(' + a + ')' );

      x := a + x + y;
   end;  { AlphaA }

   function AlphaB(a : integer): integer;
   var b : integer;
   begin { AlphaB }
      writeln( 'AlphaB(' + a + ')' );

      AlphaA(a);
   end;  { AlphaB }

begin { Main }
   writeln( 'Nested functions' );

   AlphaB(1);
end.  { Main }


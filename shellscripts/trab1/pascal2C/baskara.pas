program baskara;
var
a, b, c, delta, raizdelta, x1, x2: real;

begin
read (a);
read (b);
read (c);

	delta:= ( b*b - (4 * a * c) );
	raizdelta:= (sqrt (delta));
	x1:= ((-b +raizdelta ) / 2*a );
	x2:= ((-b -raizdelta ) / 2*a );
writeln (x1);
writeln (x2);

end.

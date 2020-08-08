program triplas;

var 
	n, m, a, b, c: integer; 

begin
Randomize;
	n:=(random(5) +1);
	m:=(random(5) +1);


	while m > n do
		m:=(random(5)+1);
	while m = n do
		m:=(random(5)+1);

	a:= (2*n*m);
	b:= ((n*n)-(m*m));
	c:= ((n*n)+(m*m));

	writeln(a);
	writeln(b);	
	writeln(c);
	
	writeln((a*a), ' + ', (b*b), ' = ', (c*c));	
	
	
end.

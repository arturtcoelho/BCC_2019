program baskara;
var
a, b, c, delta: real;

begin
read (a, b, c);
while (a<>0) or (b<>0) or (c<>0) do
	begin
		if a<>0 then
		begin		
		delta:= ( b*b - (4 * a * c) );
		if delta>0 then
			writeln(((-b -sqrt(delta) ) / 2*a ):0:2, ' ', ((-b +sqrt(delta) ) / 2*a):0:2)
			else
			if delta=0 then
				writeln((-b/2*a):0:2)
					else
					writeln('nao tem raizes reais');
		end; 
		if a=0 then 
			writeln('nao eh equacao do segundo grau');
 	read(a, b, c);	
	end;
end.

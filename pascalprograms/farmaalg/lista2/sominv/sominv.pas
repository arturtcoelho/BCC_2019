program sominv;
var
nom, den, soma, n0:real; 
begin
read(n0);
soma:=0;
nom:=1;
den:=(n0);
while nom <= n0 do 
	begin	
	soma:=soma+(nom/den);
	nom:=nom+1;
	den:=den-1;
	end;
writeln('Somatorio: ', soma:0:2);
end.

program digver;
var
dig0, ver, soma, n: longint;

begin
read (dig0);
soma:=0;
n:=2;
ver:=dig0 mod 10;
dig0:=dig0 div 10;
while dig0>0 do
	begin
	soma:=soma+(n*(dig0 mod 10));
	dig0:= dig0 div 10;
	n:=n+1;
	//writeln(soma);
	//writeln(dig0);	
	end;
if (soma mod 10)=ver then
	writeln('SIM')
		else writeln('NAO'); 
end.

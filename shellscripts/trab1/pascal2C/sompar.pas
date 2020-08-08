program sompar;
var
n, seq, soma, i:int64;
begin
read(n);
i:=0;
soma:=0;
while n <> i do
	begin
	read(seq);
		if (seq mod 2) = 0 then
		soma:= soma+seq;	
	i:=i+1;
	end;
if (n mod 2) = 0 then
	writeln(soma) 
else
	writeln('impar')
end.

program fatores;
var
n, d:longint;

//acumular o divisor de 1 em 1
//eh divisivel por div (2) -> nao, entao div := div +1
begin
read(n);	
d:=2;
while n<>1 do
	begin
	if (n mod d) = 0 then
		begin
		n:=n div d;	
		write(d, ' ')
		end
				
		else
		d:=d+1;
	end;
writeln(' ')
end.

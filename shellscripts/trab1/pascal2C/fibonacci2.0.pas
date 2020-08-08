program fibonacci2;
var
n, n1, n2, n3:int64;
begin
read(n);
n1:=1;	
n2:=1;
	while n >= 1 do
	begin
		n3:=n1+n2;	
		n1:=n2+n3;
		n2:=n3+n1;
		n:= n-1;
	end;
	writeln(n3);
end.

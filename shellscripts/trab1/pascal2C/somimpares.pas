program somimpares;
var
n0, nf, soma:int64;
begin
read(n0, nf);
soma:=0;
if (n0 mod 2 = 1) and (nf mod 2 = 1) and (n0 < nf) then 
begin
	while n0 <> nf do
	begin
	soma:= soma+n0;
	n0:= n0+2;
	end;	
	soma:=soma+nf;
end;
writeln(soma);
end.

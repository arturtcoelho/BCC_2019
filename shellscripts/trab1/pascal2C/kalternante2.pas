program kalternante;
var
par, kalt, ultimopar:boolean;
n, k, seqpar, seqimpar: integer;
begin
read(k);
kalt:=true;
seqpar:=0;
seqimpar:=0;
read(n);
while n <> 0 do
	begin
	if (n mod 2) = 0 then
		begin
		seqpar:=seqpar+1;
		if (seqimpar <> k) and (seqimpar <> 0) then
			kalt:=false;
		seqimpar:=0;
		end;
	if (n mod 2) = 1 then
		begin				
		seqimpar:=seqimpar+1;
		if (seqpar <> k) and (seqpar <> 0) then
			kalt:=false;		
		seqpar:=0;
		end;
	read(n);
	end;
if kalt=true then
writeln('Sim eh k-alternante')
else
writeln('Nao eh k-alternante')
end.

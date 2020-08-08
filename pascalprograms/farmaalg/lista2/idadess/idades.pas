program idades;
var
i, jovens, adultos, idosos:integer;
begin
i:=1;
jovens:=0;
adultos:=0;
idosos:=0;
	while i <> 0 do
	begin
	read(i);
		if (i mod 5) <> 0 then 
		begin	
		if i < 20 then
			jovens:= jovens+1
		else
		if i < 40 then
			adultos:= adultos+1
		else
		if i > 60 then
			idosos:= idosos+1
		end;
	end;
writeln('menores que 20: ', jovens);
writeln('entre 20 e 40: ', adultos);
writeln('maiores que 60: ', idosos);
end.


program segrau;
var
seg, min, grau:longint;
begin
read(seg);
min:=0;
grau:=0;
if seg >= 0 then
begin
	while seg >= 60 do
	begin
	seg:= seg - 60;
	min:= min + 1;
	end;
	//seg:= seg+60;	

	while min >= 60 do
	begin
	min:= min - 60;
	grau:= grau + 1;
	end;
	//min:=min+60;
writeln(grau,' graus, ', min, ' minutos, ', seg, ' segundos.');
end;

//writeln('Escreva um numero positivo');
end.

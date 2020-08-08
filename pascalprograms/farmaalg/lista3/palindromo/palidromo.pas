program palindromos;
var
pal, dig1, dig2, dig3, dig4, dig5, dig6:longint;
ehpal: boolean;
begin
read(pal);
dig1:=0;
dig2:=0;
dig3:=0;
dig4:=0;
dig5:=0;
dig6:=0;
ehpal:=false;
while (pal mod 10) <> 0 do
	begin
	dig1:=dig1+1;
	pal:=pal-1;
	end;
while (pal mod 100) <> 0 do
	begin
	dig2:=dig2+1;
	pal:=pal-10;
	end;
while (pal mod 1000) <> 0 do
	begin
	dig3:=dig3+1;
	pal:=pal-100;
	end;
while (pal mod 10000) <> 0 do
	begin
	dig4:=dig4+1;
	pal:=pal-1000;
	end;
while (pal mod 100000) <> 0 do
	begin
	dig5:=dig5+1;
	pal:=pal-10000;
	end;
while (pal mod 1000000) <> 0 do
	begin
	dig6:=dig6+1;
	pal:=pal-100000;
	end;
(*
writeln(dig6);
writeln(dig5);
writeln(dig4);
writeln(dig3);
writeln(dig2);
writeln(dig1);
*)
if dig6=0 then
	if (dig5 = dig1) and (dig4 = dig2) then
		ehpal:=true;
if dig6<>0 then
	if (dig6 = dig1) and (dig5 = dig2) and (dig4 = dig3) then
		ehpal:=true;

if ehpal=true then
	writeln('Sim eh palindromo')
	else writeln('Nao eh palindromo');
end.

program mediaponderada;
var
m, n, p, media, nom, den:real;
div0: boolean;
begin
nom:=0;
den:=0;
read(m);
div0:=false;
if m=0 then
	div0:=true;
while (m<>0) do
	begin
	read(n, p);
	nom:=(nom+(n*p));
	den:=(den+(p));
	m:=m-1;
	end;
if (div0=false) and (den<>0) then
	writeln(nom/den)
	else writeln('divisao por zero')
end.

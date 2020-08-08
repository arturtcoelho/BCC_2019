program expressaoaritimetica;
var
a,b,c,d,e,f,den0,nom0,den1,den2:real;
begin
read(a,b,c,d,e,f);
den1:=c-d;
den2:=a*b;
if (den1<>0) and (den2<>0) then
	begin
	nom0:=((a+b)/den1)*e;	
	den0:=(f/den2)+e;
	if den0<>0 then
		writeln(nom0/den0)
		else writeln('divisao por zero'); 
	end
	else writeln('divisao por zero');
end.

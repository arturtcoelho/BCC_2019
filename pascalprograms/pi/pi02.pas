program pi02;
var
pi, sinal, impar, n:real;
begin
pi:=4;
impar:=3;
n:=0;
sinal:=(-1);
while n < 5000000000 do (*9 casas decimais*)
	begin
	pi:=pi+(sinal*(4/impar));
	sinal:=sinal*(-1);
	impar:=impar+2;
	n:=n+1;
	end;
writeln(pi);
end.

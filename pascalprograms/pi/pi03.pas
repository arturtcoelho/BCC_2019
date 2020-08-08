program pi03;
var
pi, n, n1, n2, n3, sinal: real;
begin
pi:=3;
sinal:=1;
n1:=2;
n2:=3;
n3:=4;
n:=0;
while n < 900000000 do (*13 casas decimais*)
	begin
	pi:=pi+(sinal*(4/(n1*n2*n3)));	
	n1:=n1+2;
	n2:=n2+2;
	n3:=n3+2;
	n:=n+1;
	sinal:=sinal*(-1);
	//writeln(pi);	
	end;
writeln(pi);
end.

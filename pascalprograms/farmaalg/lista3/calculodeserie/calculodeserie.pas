program calculodeserie;

var
soma, anterior, fatorial, n, sinal:real;

begin
soma:=1;
anterior:=0;
fatorial:=2;
sinal:=-1;
n:=2;
while (abs(anterior-soma) > 0.000001) do
	begin
	anterior:=soma;
	soma:=soma+(sinal*(1/fatorial));
	sinal:=sinal*(-1);
	n:=n+1;	
	fatorial:=(fatorial*n);
	n:=n+1;
	fatorial:=(fatorial*n);	
writeln(soma:0:15);
	end;
writeln(soma:0:15);
end.

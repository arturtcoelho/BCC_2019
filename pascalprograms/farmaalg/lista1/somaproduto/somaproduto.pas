program somaproduto;
var
a,b,c,d,dor,pn,pd,sn,sd:int64;
begin
read(a, b);
read(c, d);
	
pn:=a*c;
pd:=b*d;

dor:=d;

c:=(c*b);
d:=(d*b);
a:=(a*dor);
b:=(b*dor);

sn:=(a+c);
sd:=(pd);
	writeln('A soma = ', sn, ' / ', sd);
	writeln('O produto = ', pn, ' / ', pd);
end.

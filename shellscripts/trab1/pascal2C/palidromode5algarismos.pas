program palindromo;
var
pal, dig1, dig2, dig3, dig4, dig5:longint;
begin
read(pal);
dig1:=pal div 10000;
dig2:=(pal-(dig1*10000)) div 1000;
//dig3 nao importa no final, porem no meio
dig3:=(pal-((dig1*10000)+(dig2*1000)) div 100);
dig4:=(pal-((dig1*10000)+(dig2*1000)+(dig3*100)) div 10);
dig5:=(pal-(dig1*10000)+(dig2*1000)+(dig3*100)+(dig4*10));
if (dig1 = dig5) and (dig2 = dig4) then
	writeln('Sim eh palindromo')
else writeln('Nao eh palindromo')
end.



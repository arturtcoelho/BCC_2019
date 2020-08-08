program media;

const MAX = 100;

type vetorreal = array [1..MAX] of real;

procedure lerarray (var v: vetorreal; tam: longint);
var i:longint;
begin
	for i:=1 to tam do
	begin
		read(v[i]);
	end; 
end;

procedure imprimirresultados (var v1, v2, v3: vetorreal; tam: longint);
var i :longint; nota: real; status: string;
begin
	for i:=1 to tam do
	begin
		nota:=(v1[i]+2*v2[i]+3*v3[i])/6;
		if nota >= 70 then
			status:='Aprovado'
		else
		if nota >= 40 then
			status:='Final'
		else 
			status:='Reprovado';
		writeln('Aluno ', i,': ', (nota:0:2), ' ', status);
	end;	
end;

var
	tam: longint;
	notas1, notas2, notas3: vetorreal;
	
begin
	read(tam);
	lerarray(notas1, tam);
	lerarray(notas2, tam);
	lerarray(notas3, tam);
	imprimirresultados(notas1, notas2, notas3, tam);
end.

program eqlinear;

const MAX = 10;

type 
	elemento = longint;
	matriz = record
		l, c: longint;
		m: array [1..MAX,1..MAX] of elemento
		end;
	vetor = array [1..MAX] of elemento;

var	m: matriz;
	coeficientes, resultados: vetor;
	correto: boolean;

procedure lerdimensoes (var m: matriz);
begin
	read(m.l, m.c);
end;

procedure lervetor (var v: vetor; tam: longint);
var i: longint;
begin
	for i:=1 to tam do
		read(v[i]);
end;

function calculo (var m: matriz; var coeficientes, resultados: vetor): boolean;
var	ok: boolean;
	i, j: longint;
	soma: elemento;
begin
	ok:=true;
	i:=1;
	j:=1;
	while (ok) and (i <= m.l) do
	begin
		soma:=0;
		j:=1;
		while (ok) and (j <= m.c) do
		begin
			soma:=soma+(coeficientes[j] * m.m[i,j]);
			j:=j+1;
		end;
		if soma <> resultados[i]  then
			ok:=false;
		i:=i+1;
	//	writeln(soma);
	//	writeln(ok);
	end;
	calculo:=ok;
end;

procedure lermatriz (var m: matriz);
var i, j: longint;
begin
	for i:=1 to m.l do
		for j:=1 to m.c do
			read(m.m[i,j]);
end;

begin
	//ler entradas
	lerdimensoes(m);
	lervetor(coeficientes, m.c);
	lermatriz(m);
	lervetor(resultados, m.l);

	//imprimirresultado
	if calculo(m, coeficientes, resultados) then
		writeln('sim')
	else
		writeln('nao');
end.
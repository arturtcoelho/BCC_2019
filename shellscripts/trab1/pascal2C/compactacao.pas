program compactacao;

const MAX = 100;

type vetor = array [0..MAX] of longint;

procedure lervetor (var v: vetor; tam: longint);
var i: longint;
begin
	for i:=1 to tam do
		read(v[i]);
end;

function naoesta (x :longint;var v: vetor): boolean;
var i, cont: longint;
begin
	cont:=0;
	for i:=1 to v[0] do
	begin
		if x=v[i] then
		cont:=cont+1;
	end;
	if cont=0 then
		naoesta:= true
	else
		naoesta:= false;
end;

procedure compactar (var r, f: vetor;var tam: longint);
var i, j: longint;
begin
	r[0]:=tam;
	j:=0;
	for i:=1 to r[0] do
	begin
		if naoesta(r[i], f) then
		begin
			j:=j+1;
			f[j]:=r[i];
			f[0]:=j;		
		end;
	end;	
	tam:=j;
end;

procedure impressaooriginal (var v :vetor; tam: longint);
var i: longint;
begin
	write('O: ');
	for i:=1 to tam do
		write(v[i]);
	writeln;
end;

procedure impressaocompactada (var v :vetor; tam: longint);
var i: longint;
begin
	write('C: ');
	for i:=1 to tam do
		write(v[i], ' ');
	writeln;
end;

var
	tam: longint;
	v, c: vetor;
	
begin
	read(tam);
	while tam <> 0 do
	begin
		lervetor(v, tam);
		impressaooriginal(v, tam);
		compactar(v, c, tam);
		impressaocompactada(c, tam);
		read(tam);
	end;	
end.

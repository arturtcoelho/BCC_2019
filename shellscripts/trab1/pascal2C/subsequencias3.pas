program subsequencia2;

const MAX = 100;

type vetor = array [0..MAX] of longint;

var
	v, p: vetor;
	tam, i, x: longint;
//	achei: boolean;

procedure lervetor (var v: vetor; tam: longint);
var  i: longint;
begin
	for i:=1 to tam do
		read(v[i]);
	v[0]:=tam;
end;

procedure gerarsub (var sub, v: vetor; tamsub, pos: longint);
var j: longint;
begin
	pos:=pos-1;
	for j:=pos to tamsub do
		sub[j]:=v[pos+j];
	sub[0]:=j;
end;

function esta (x: longint;var v: vetor): boolean;
var i, cont: longint;
begin
	cont:=0;
	for i:=1 to v[0] do
	begin
		if v[i]=x then
			cont:=cont+1;
	end;
	if cont>1 then
		esta:=true
	else
		esta:=false;
end;

procedure adicionar (x, pos: longint;var v: vetor);
begin
	v[tam]:=x;
	v[tam+1]:=pos;
	v[0]:=v[0]+2;
end;

procedure imprimir (var v: vetor);
var i: longint;
begin
	for i:=1 to v[0] do
		write(v[i], ' ');
	writeln;
end;

begin
	p[0]:=0;
	read(tam);
	lervetor(v, tam);
	i:=1;
	while (i<=tam) do
	begin
		x:=v[i];
		if esta(x, v) then
			adicionar(x, i, p);
		i:=i+1;
	end;
	imprimir(p);
end.

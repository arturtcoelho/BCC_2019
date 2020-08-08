program subsequencia4;

const MAX = 100;

type vetor = array [0..MAX] of longint;

procedure lervetor (var v: vetor; tam: longint);
var  i: longint;
begin
	for i:=1 to tam do
		read(v[i]);
	v[0]:=tam;
end;

function esta (x :longint;var v: vetor): boolean;
var i, cont: longint;
begin
	cont:=0;
	for i:=1 to v[0] do
	begin
		if x=v[i] then
		cont:=cont+1;
	end;
	if cont=0 then
		esta:= false
	else
		esta:= true;
end;

procedure imprimirvetor (var v: vetor);
var i: longint;
begin
	for i:=1 to v[0] do
		write(v[i], ' ');
	writeln;
end;

var
	tam: longint;
	v: vetor;

begin
	read(tam);
	lervetor(v, tam);
	
end.

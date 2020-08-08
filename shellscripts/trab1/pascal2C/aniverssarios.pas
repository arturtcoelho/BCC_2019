program aniverssarios;

const MAX = 100;

type vetor = array [0..MAX] of longint;

procedure lervetor (tam: longint;var v: vetor);
var i: longint;
begin
	for i:=1 to tam do
		read(v[i]);
end;

(*function repetidos (x, tam: longint;var v: vetor): longint;
var i, rep: longint;
begin
	rep:=0;
	for i:=1 to tam do
	begin
		if x = v[i] then 
			rep:=rep+1;
	end;
	repetidos:=rep div 2;
end;*)

(*procedure calcrep (var tam, rep: longint; var v: vetor);
var i, j, x: longint;
begin
	for i:=1 to tam do
	begin
		x:=v[i];
		for j:=1 to tam do
		begin
			if v[j] = x then
				rep:=rep+1;
		end;
	end;
end;*)

function ehrepetido (tam: longint; var v: vetor): boolean;
var i, rep, x, j: longint;
begin
	for i:=1 to tam do
	begin
		x:=v[i];
		for j:=1 to tam do
		begin
			if v[j] = x then
				rep:=rep+1;
		end;
	end;
	if rep > tam then
		ehrepetido:=true
	else 
		ehrepetido:=false;
end;

var
	tam, i, rep: longint;
	v: vetor;

begin
	read(tam);
	for i:=1 to 100 do
	begin
		lervetor(tam, v);
		if ehrepetido(tam, v) then
			rep:=rep+1;
	end;
	writeln((rep/100):0:2);
end.

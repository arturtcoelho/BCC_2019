program subsequencia2;

const MAX = 100;

type vetor = array [0..MAX] of longint;

var
	v, sub: vetor;
	tam, tamsub, pos: longint;
	achei: boolean;

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

function conferetudo (var sub, v: vetor; pos: longint): boolean;
var i, cont: longint;
begin
	cont:=0;
	for i:=1 to sub[0] do 
	begin
		if sub[i]=v[pos+i-1] then
			cont:=cont+1;
	end;
	if cont=sub[0] then
		conferetudo:=true
	else
		conferetudo:=false;
end;

function conferirsub (var sub, v: vetor): boolean;
var	achei: boolean;
	i: longint;
begin
	i:=1;
	achei:=false;
	while not(achei) and (sub[1]<>(v[0]-sub[0])) do
	begin
		if sub[1]=v[i] then
			achei:=conferetudo(sub, v, i);
		i:=i+1;
	end;
		conferirsub:=achei;
end;

procedure imprimir (var v: vetor);
var i: longint;
begin
	for i:=1 to v[0] do
		write(v[i], ' ');
	writeln;
end;

begin
	read(tam);
	lervetor(v, tam);
	tamsub:=tam div 2;
	achei:=false;
	while not(achei) and (tamsub >= 2) do
	begin
		pos:=1;
		while not(achei) and (pos<>tam) do
		begin
			gerarsub(sub, v, tamsub, pos);
			achei:=conferirsub(sub, v);
			pos:=pos+1;
		end;
		tamsub:=tamsub-1;				
	end;
//	writeln((sub[1]<>(v[0]-sub[0])));
	if (achei) then
		writeln(pos-1, ' ', tamsub+1)
	else
		writeln('nenhuma');
end.

program subsequencias;
 
const MAX = 100; 

type vetor = array [0..MAX] of longint;

procedure lervetor (var v: vetor; tam: longint);
var  i: longint;
begin
	for i:=1 to tam do
		read(v[i]);
	v[0]:=tam;
end;

procedure gerarsub (var sub, v: vetor; tams, pos: longint);
var j: longint;
begin
	//pos:=pos-1;
	for j:=pos to tams do
		sub[j]:=v[pos+j];
	sub[0]:=j;
end;

procedure conferirsub (var sub, v: vetor;var pos, achei: longint);
//faz essa merda agora otario
var i, cont, j: longint;
	subc: vetor;
begin
	for i:=pos+sub[0] to v[0]-sub[0] do
	begin
		cont:=0;
		gerarsub(subc, v, sub[0], i);
		for j:=1 to subc[0] do
		begin
			if sub[j]=subc[j] then
				cont:=cont+1;
		end;
		if cont=sub[0] then
			achei:=pos;
	end;
end;

function temsub (var v: vetor; tams: longint): longint;
var i, achei, lim, a: longint;
	sub: vetor;
begin
	a:=1;
	achei:=0;
	lim:=v[0]-tams;
	while (achei=0) and (a <= lim) do
	begin
		gerarsub(sub, v, tams, a);
		conferirsub(sub, v, a, achei);
		a:=a+1;
	end;
	temsub:=achei;
end;

procedure imprimir (var v: vetor);
var i: longint;
begin
	for i:=1 to v[0] do
		write(v[i], ' ');
	writeln;
end;

var
	tam, tams, x: longint;
	v: vetor;
	
begin
	x:=0;
	read(tam);
	lervetor(v, tam);
	tams:= tam div 2;
	while (x = 0) and (tams >= 2) do
	begin
		x:=temsub(v, tams);
		tams:=tams-1;
	end;
	if x > 0 then
		writeln(x, ' ', tams+1)
	else
		writeln('nenhuma');
end.
//vai tomar no cu programa do krl vsf o merda

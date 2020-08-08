program repmatriz;

const MAX = 100;

type
	matriz = record
	l, c:longint;
	m: array [1..MAX,1..MAX] of longint;
	end;

procedure lermatriz (var m: matriz);
var i, j: longint;
begin
	read(m.l);
	read(m.c);
	for i:=1 to m.l do
		for j:=1 to m.c do
			read(m.m[i,j]);
end;

function esta (x:longint; m: matriz): boolean;
var i, j, cont: longint;
begin
	cont:=0;
	for i:=1 to m.l do
		for j:=1 to m.c do 
		begin	
			if x=m.m[i,j] then
				cont:=cont+1;
		//	writeln(cont);
		end;
	if cont>1 then
		esta:=true
	else
		esta:=false;
end;

function ehrep (m: matriz):boolean;
var i, j:longint;
begin
	ehrep:=false;
	for i:=1 to m.l do
		for j:=1 to m.c do
			if esta(m.m[i,j], m) then
				ehrep:=true;
end;

procedure impr (var m: matriz);
var i, j: longint;
begin
	for i:=1 to m.l do
	begin
		for j:=1 to m.c do
			write(m.m[i,j], ' ');
		writeln;
	end;
end;

var
	m: matriz;

begin
	lermatriz(m);
	if ehrep(m) then
		writeln('sim')
	else
		writeln('nao');	
//	impr(m);
end.

o
s;

const MAX = 100;

type
	matriz = record
		c, l:longint;
		m: array [1..MAX,1..MAX] of longint;
	end;

procedure lermatriz (var m: matriz);
var i, j: longint;
begin
	read(m.l);
	m.c:=m.l;
	for i:=1 to m.l do
		for j:=1 to m.c do 
			read(m.m[i,j]);
end;

function conflinhas (m: matriz): longint;
var i, j, x: longint;
begin
	conflinhas:=0;
	for i:=1 to m.l do
	begin
		x:=0;
		for j:=1 to m.c do
		begin
			x:=x+m.m[i, j];
		end;
		if x=1 then
			conflinhas:=conflinhas+1;
	end;		
end;

function confcolunas (m: matriz): longint;
var i, j, x: longint;
begin
	confcolunas:=0;
	for i:=1 to m.c do
	begin
		x:=0;
		for j:=1 to m.l do
		begin
			x:=x+m.m[j, i];
		end;
		if x=1 then
			confcolunas:=confcolunas+1;
	end;		
end;

var
	m: matriz;

begin
	lermatriz(m);
	if (conflinhas(m)=m.l) and (confcolunas(m)=m.c) then
	    writeln('sim')
	else
	    writeln('nao');
end.


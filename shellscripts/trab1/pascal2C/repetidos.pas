program repetidos;

const MAX = 100;

type vetor = array [0..MAX] of longint;

procedure lervetor (var v: vetor);
var n, tam: longint;
begin
	read(n);
	tam:=0;
	while n <> 0 do
	begin
		tam:=tam+1;
		v[tam]:=n;
		read(n);
	end;
	v[0]:=tam;
end;

function repetido (x: longint; var v: vetor): boolean;
var i, cont:longint;
begin
	cont:=0;
	for i:=1 to v[0] do
	begin
		if v[i]=x then
			cont:=cont+1;
	end;
	if cont=1 then
		repetido:= false
	else 
		repetido:= true;
end;

procedure processo (var v, r: vetor);
var i, j: longint;
begin
	j:=0;
	for i:=1 to v[0] do
	begin
		if repetido(v[i], v) then
		begin
			j:=j+1;
			r[j]:=v[i];
		end;
	end;
	r[0]:=j;	
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

procedure removerrepetidos (var r, f: vetor);
var i, j: longint;
begin
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
	f[0]:=j;
end;

procedure imprimirvetor (var v: vetor);
var i: longint;
begin
	for i:=1 to v[0] do
		write(v[i], ' ');
	writeln;
end;

var 
	v, r, f: vetor;
	
begin
	lervetor(v);
	processo(v,r);
	removerrepetidos(r, f);
	imprimirvetor(f);
end.

program uniao;

const MAX = 200;

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

procedure uniao (var A, B, C: vetor);
var i, tam: longint;
begin
	tam:=1;
	for i:=1 to A[0] do
	begin
		C[tam]:=A[i];
		tam:=tam+1;
	end;
	for i:=1 to B[0] do
	begin
		C[tam]:=B[i];
		tam:=tam+1;
	end;	
	C[0]:=tam;	
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
	for i:=1 to v[0]-1 do
		write(v[i], ' ');
	writeln;
end;

var
	A, B, C, D: vetor;

begin
	lervetor(A);
	lervetor(B);
	uniao(A,B,C);
	removerrepetidos(C, D);
	imprimirvetor(D);
end.

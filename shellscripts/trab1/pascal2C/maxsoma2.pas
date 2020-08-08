program maxsoma;

const MAX = 1000;

type vetor = array [0..MAX] of longint;

procedure lervetor (var v: vetor; tam: longint);
var i: longint;
begin
	for i:=1 to tam do
		read(v[i]);	
	v[0]:=tam;
end;

procedure adicionar (var v: vetor; x: longint);
begin
	v[0]:=v[0]+1;
	v[v[0]]:=x;
end;

function defmaior (var v: vetor): longint;
var i, maior: longint;
begin
	maior:=v[1];
	for i:=1 to v[0] do
	begin
		if v[i]>maior then
			maior:=v[i];	
	end;
	defmaior:=maior;
end;	

function soma (var v: vetor; caixa, p: longint): longint;
var s, i: longint;
begin
	s:=0;
	p:=p-1;
	for i:=1 to caixa do
		s:=s+v[p+i];
	soma:=s;
end;

procedure somasdacaixa (var v, s: vetor; caixa: longint);
var i: longint;
begin
	for i:=1 to v[0] do
		adicionar(s, soma(v, caixa, i));
end;

var
	tam, caixa: longint;
	v, s, maiores: vetor;

begin
	read(tam);
	lervetor(v, tam);
	for caixa:=1 to tam do
	begin
		somasdacaixa(v, s, caixa);
		adicionar(maiores, defmaior(s));
	end;
	writeln(defmaior(maiores));
end.

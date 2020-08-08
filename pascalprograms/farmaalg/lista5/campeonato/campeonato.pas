program campeonato;

const MAX = 20;

type	a_string = array [1..MAX] of string;
		a_int = array [1..MAX] of longint;

procedure ler_array_string (var v: a_string ; tam: longint);
var i: longint;
begin
	i:=1;
	while i<=(tam+1) do
	begin
		readln(v[i]);
		i:=i+1;
	end;
end;

procedure ler_array_integer (var v: a_int; tam: longint);
var i: longint;
begin
	for i:=1 to tam do
	begin
		read(v[i]);
	end;
end;
(*
procedure imprimir_array_string (var v: a_string; tam: longint);
var i: longint;
begin
	for i:=1 to (tam+1) do
	begin
		write(v[i], ' '); 
	end;
	writeln;
end;

procedure imprimir_array_integer (var v: a_int; tam: longint);
var i: longint;
begin
	for i:=1 to tam do
	begin
		write(v[i], ' '); 
	end;
	writeln;
end;
*)
function defcampeao (var v: a_int; tam: longint): longint;
var i, indice, maior: longint;
begin
	maior:=v[1];
	indice:=1;
	for i:=1 to tam do
	begin
		if maior <= v[i] then
		begin
			indice:=i;
			maior:=v[i];
		end;
	end;	
	defcampeao:=indice;
end;

var
	times: a_string;
	pontuacao: a_int;
	tamanho, campeao: longint;

begin
	read(tamanho);
	ler_array_string(times, tamanho);
	ler_array_integer(pontuacao, tamanho);
	campeao:=defcampeao(pontuacao, tamanho);
	writeln('O campeao eh o ',times[campeao+1]);
end.


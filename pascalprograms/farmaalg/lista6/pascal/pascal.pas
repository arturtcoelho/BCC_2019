program pascal;

const MAX = 100;

type vetor = array [0..MAX] of qword;

function power (b, e: qword): qword;
var i: longint;
begin
	power:=b;
	i:=1;
	if e > 0 then
	begin
		while i < e do
		begin
			power:=b*power;
			i:=i+1;
		end;
	end
	else
	power:=1;
end;

function fat (x: qword): qword;
var i: longint;
begin
	fat:=1;
	for i:=x downto 1 do
		fat:=fat*i;
end;

function elemento (l, c: qword): qword; 
begin
	elemento:=(fat(l) div (fat(c)*fat(l-c)));
end;

procedure gerarlinha (l: longint;var v: vetor);
var i, tam: longint;
begin
	tam:=0;
	for i:=1 to l do
	begin
		v[i]:=elemento(l, i);
		tam:=i;
	//	write('a');
	end;	
	v[0]:=tam;
	//writeln(v[0]);
end;

procedure imprimirvetor (var v: vetor);
var i: longint;
begin
	write(1, ' ');
	for i:=1 to v[0] do
		write(v[i], ' ');
	writeln;
end;

var
	i, linhas: longint;
	v: vetor;
	
begin
	read(linhas);
	writeln(1);
	for i:=1 to linhas-1 do
	begin
		gerarlinha(i, v);
		imprimirvetor(v);
	end;
end.

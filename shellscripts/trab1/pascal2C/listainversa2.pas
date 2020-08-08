program listainversa2;

const MAX = 100;

type vetor = array [0..MAX] of longint;

procedure lervetor (var v: vetor);
var i, n: longint;
begin
	i:=0;
	read(n);
	while n<>0 do
	begin
		i:=i+1;
		v[i]:=n;
		read(n);
	end;
	v[0]:=i;
end;

procedure imprimirinverso (var v: vetor);
var i: longint;
begin
	for i:=v[0] downto 1 do
		write(v[i], ' ');
	writeln;
end;

var
	a, b: vetor;

begin
	lervetor(a);
	lervetor(b);
	imprimirinverso(a);
	imprimirinverso(b);
end.

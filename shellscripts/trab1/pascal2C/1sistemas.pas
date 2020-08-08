program sistemas1.pas;

{Le uma matriz, que eh um sistema linear com variaveis (a, b, c...),
 permite fazer operacoes (multiplica/divide linha/coluna, soma/subtrai linhas/colunas,
 e permite permutar colunas entre se e linhas entre si.
 Exibe a cada operacao o sistema atualizado}

const MAX = 10;

type 	elemento = real;
	sistema = record
		l, c: longint;
		m: array [1..MAX,1..MAX] of elemento;
		v: array [1..MAX] of string[1];
		end;

procedure atribuirvariaveis (var s: sistema);
var i: longint;
begin
	for i:=1 to s.c-1 do
	begin
		case i of
		1:s.v[i]:='a';2:s.v[i]:='b';3:s.v[i]:='c';
		4:s.v[i]:='d';5:s.v[i]:='e';6:s.v[i]:='f';
		else s.v[i]:='x';
		end;
	end;
end;

procedure lersistema (var s: sistema);
var i, j: longint;
begin
	read(s.l);
	s.c:=s.l+1;
	for i:=1 to s.l do
		for j:=1 to s.c do
			read(s.m[i,j]);
	atribuirvariaveis(s);
end;

procedure imprimirsistema (s: sistema);
var i, j: longint;
begin
	for i:=1 to s.l do
	begin
		for j:=1 to s.c-1 do
			write(s.m[i,j]:0:2, s.v[j],' ');
		write('= ', s.m[i,j]:0:2);
		writeln;
	end;
end;

procedure escrever_operacoes;
begin
	writeln('Operacoes disponiveis:');
	writeln('0: encerra o programa');
	writeln('1: multiplicar linha x por y');
	writeln('2: divide linha x por y');
	writeln('3: soma linha x com y');
	writeln('4: subtrai linha x da y');
	writeln('5: troca linhas x com y');
	writeln('6: troca colunas x com y');
//	writeln('');
end;

procedure multiplica (var s: sistema; x, y: longint);
var i: longint;
begin
	for i:=1 to s.c do
		s.m[x,i]:=s.m[x,i]*y;
	imprimirsistema(s);
end;

procedure divide (var s: sistema; x, y: longint);
var i: longint;
begin
	for i:=1 to s.c do
		s.m[x,i]:=s.m[x,i]/y;
	imprimirsistema(s);
end;

procedure soma (var s: sistema; x, y: longint);
var i: longint;
begin
	for i:=1 to s.c do
		s.m[x,i]:=s.m[y,i]+s.m[x,i];
	imprimirsistema(s);
end;

procedure subtrai (var s: sistema; x, y: longint);
var i: longint;
begin
	for i:=1 to s.c do
		s.m[x,i]:=s.m[x,i]-s.m[y,i];
	imprimirsistema(s);
end;

procedure copiarsistema (var o, c: sistema);
var i, j: longint;
begin
	for i:=1 to o.l+1 do
		for j:=1 to o.c do
			c.m[i,j]:=o.m[i,j];
end;

procedure trocalinhas (var s: sistema; x, y: longint);
var c: sistema;
	i: longint;
begin
	copiarsistema(s, c);
	for i:=1 to s.l+1 do
		s.m[x,i]:=c.m[y,i];
	for i:=1 to s.l+1 do
		s.m[y,i]:=c.m[x,i];
	imprimirsistema(s);
end;

procedure trocacolunas (var s: sistema; x, y: longint);
var c: sistema;
	i: longint;
begin
	copiarsistema(s, c);
	for i:=1 to s.l do
		s.m[i,x]:=c.m[i,y];
	for i:=1 to s.l do
		s.m[i,y]:=c.m[i,x];
	imprimirsistema(s);
end;

var 	s: sistema;
	x, y, entrada: longint;
	
{=============================programa principal===================================}
begin
	writeln('Escreva seu sistema');
	lersistema(s);
	repeat
		escrever_operacoes;
		read(entrada);
		if entrada<>0 then
			read(x, y); {dados da operacao, longint 
			(utilizado como parametro implementar sendo possivel ser real, para multiplicar/dividir}
		case entrada of
			0:writeln('FIM');
			1:multiplica(s, x, y);
			2:divide(s, x, y);
			3:soma(s, x, y);
			4:subtrai(s, x, y);
			5:trocalinhas(s, x, y);
			6:trocacolunas(s, x, y);
		{cada operacao ja escreve o sistema}
			else;
		end;
	until entrada=0;
	imprimirsistema(s);
end.
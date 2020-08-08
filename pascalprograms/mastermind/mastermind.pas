program mastermind;

const 	MAX = 4;
		CORES = 6;
		NUMT = 10;

type vetor = array [0..MAX] of longint;

procedure gerarsenha (var v: vetor);
var i: longint;
begin
	for i:=1 to MAX	 do
		v[i]:=random(CORES)+1; 
	v[0]:=MAX
end;

procedure imprimirvetor (var v: vetor);
var i: longint;
begin
	for i:=1 to v[0] do
		write(v[i], ' ');
	writeln;	
end;

procedure lerchute (var v: vetor);
var i: longint;
begin
	for i:=1 to MAX do
		read(v[i]);
	v[0]:=MAX;
end;

function esta (x: longint; var v: vetor): boolean;
var i: longint;
begin
	esta:=false;
	for i:=1 to MAX do
		if x = v[i] then
			esta:= true;
end;

function teste (x, pos: longint;var s: vetor): longint;
begin
	if x = s[pos] then
		teste:=3
	else
	if esta(x, s) then
		teste:=2
	else
		teste:=1;
end;

function ganhou (var v: vetor): boolean;
var i, cont: longint;
begin
	cont:=0;
	ganhou:= false;
	for i:=1 to MAX do
		if (v[i] = 3) then
			cont:=cont+1;
	if cont=MAX then
		ganhou:=true;
end;

procedure resposta (var senha, chute, res: vetor; var status: boolean);
var x, i, pos, esta: longint;
begin
	for i:=1 to MAX do
	begin
		pos:=0;
		esta:=0;
		x:=teste(chute[i], i, senha);
		if x = 1 then
			res[i]:=(1)
		else
		if x = 2 then
			begin
			res[i]:=(2);
			esta:=esta+1;
			end
		else
		if x = 3 then
			begin
			res[i]:=(3);
			pos:=pos+1;
			end;
		
	end;
	writeln(esta, ' ', pos);
	if ganhou(res) then
		status:=true;
	writeln;
end;

procedure organizarresposta (var v, r: vetor);
var i, j: longint;
begin
	j:=0;
	for i:=1 to MAX do
	begin
		if (v[i]=2) or (v[i]=3) then
		begin
			r[j]:=v[i];
			j:=j+1;
		end;
	end;
	r[0]:=j;
end;

//programa principal

var
	senha, chute, res, reso: vetor;
	status: boolean;
	tentativas: longint;

begin
	randomize;
	gerarsenha(senha);
//	imprimirvetor(senha);
	status:=false;
	tentativas:=NUMT;
	res[0]:=MAX;
	while (not(status)) and (tentativas >= 1) do
	begin
		lerchute(chute);
		resposta(senha, chute, res, status);
//		organizarresposta(res, reso);
//		imprimirvetor(res);
		tentativas:=tentativas-1;
	end;
	if status then
		writeln('GANHOU!')
	else
		writeln('perdeu...');
end.
(*	Original: 6 cores e 10 fileiras
	Numeros: 10 numeros e 10 fileiras (da tambem a soma dos numeros, da senha e do chute)
	Palavras: 26 letras, apenas palavras validas, mais tentativas (qual tamanho?)
	Palavras 2.0: indica para cada letra se esta acima ou abaixo no alfabeto*)

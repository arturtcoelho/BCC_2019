program chess;

uses Crt;

const 	
	MAX = 8;

(*tabuleiro carrega a matriz de inteiros, cada um representa uma peca
status do fim da partida e o turno
numero de jogadas*)
type
	tabuleiro = record
		m: array [0..MAX+1,0..MAX+1] of integer;
		fim, turno: boolean;
		jogadas: integer;
	end;

(*quando a jogada eh lida, se le a origem e o destino da peca*)
	jogada = record
		a, b, x, y: longint;
		validade: boolean;
	end;

var
	tab: tabuleiro;
	j: jogada;

(*whites = 10:pawn, 20: rook, 30: knight, 40: bishop, 50: Queen, 60: King*)
(*blacks = 11:pawn, 12: rook, 13: knight, 14: bishop, 50: Queen, 60: King*)
(*turno = true: brancas, false: pretas*)
procedure criartabuleiro (var tab: tabuleiro);
var i, j: longint;
begin
	tab.m[1,1]:=20;
	tab.m[1,2]:=30;
	tab.m[1,3]:=40;
	tab.m[1,4]:=60;
	tab.m[1,5]:=50;
	tab.m[1,6]:=40;
	tab.m[1,7]:=30;
	tab.m[1,8]:=20;
	//peoes brancos
	for i:=1 to 8 do
		tab.m[2,i]:=10;
	//espacos vazios
	for i:=3 to 6 do
		for j:=1 to 8 do
			tab.m[i,j]:=0;
	//peoes pretos 
	for i:=1 to 8 do
		tab.m[7,i]:=11;
	tab.m[8,1]:=12;
	tab.m[8,2]:=13;
	tab.m[8,3]:=14;
	tab.m[8,4]:=16;
	tab.m[8,5]:=15;
	tab.m[8,6]:=14;
	tab.m[8,7]:=13;
	tab.m[8,8]:=12;
	//turno comeca nas brancas
	tab.jogadas:=0;
	tab.turno:=true;
end;

function testapeao (j: jogada; tab: tabuleiro): boolean;
(*casos:
1: primeira jogada anda 2
	1.1: nao pode ter ninguem no local
	1.2: nao pode ter ninguem antes
2: anda 1 reto, nao pode ter ninguem
3: anda diagonal, tem que ter alguem, caso seja amigo ha outro caso para testar
4: anda mais que 2*)
var destino: integer;
	col, maisq, um, diagonal, prim, dois, ok: boolean;
begin
	ok:=true;
	destino:=tab.m[j.x,j.y];
	//primeira jogada
	if tab.turno then
		prim:= j.a=2
	else
		prim:= j.a=7;

	if tab.turno and prim then
		col:= tab.m[j.a+1,j.b]<>0;
	if not(tab.turno) and prim then
		col:= tab.m[j.a-1,j.b]<>0;

	dois:= abs(j.a-j.x)=2;
	um:= abs(j.a-j.x)=1;
	maisq:= abs(j.a-j.x)>2;
	diagonal:= (j.b<>j.y);
	//4
	if maisq then
		ok:=false;
	//1
	if ok and (dois and not(prim)) then
		ok:=false;
	//1.1
	if ok and dois and (destino<>0) then
		ok:=false;
	//1.2
	if col and not(diagonal) then
		ok:=false;
	//3	
	if ok and (diagonal and (destino=0)) then
		ok:=false;
	//2
	if ok and (um and not(diagonal) and (destino<>0)) then
		ok:=false;
		testapeao:=ok;
end;

function testecolisao (j: jogada; tab: tabuleiro; peca: integer): boolean;
(*1:norte, 2:leste, 3: sul, 4: oeste, 
5: nordeste, 6:sudeste, 7:sudoeste, 8:noroeste*)
var	direcao: integer;
begin
	case peca of
		1:testecolisao:=false;
		6:testecolisao:=false
		3:testecolisao:=false;
		else
		begin
			case peca of
				//torre
				2:begin
					i:=1;
					horizontal:= j.a=j.x;
					direita:=j.b>j.y;
					baixo:=j.a>j.x;
					if horizontal and direita then
						while
						(*faz essa porra ae o corno 

							quem foi que inventou de fazer essas merda

								nao desiste do codigo nao o arrombado*)
				end;
				//bispo
				4:begin

				end;
				//rainha
				5:begin

				end;
				else testecolisao:=true;
			end;
		end;
	end;
end;

function testelugarocupado (j: jogada; tab: tabuleiro; peca: integer): boolean;
//testa se tem uma peca sua la
var destino: integer;
begin
	testelugarocupado:=false;
	destino:=tab.m[j.x, j.y];
	if destino = 0 then
		testelugarocupado:=true
	else
		if (tab.turno) then
			if (destino mod 10) = 0 then
				testelugarocupado:=false
			else
				testelugarocupado:=true
		else
			if (destino mod 10) <> 0 then
				testelugarocupado:=false
			else
				testelugarocupado:=true;	
end;

function testemovimento (j: jogada; peca: integer): boolean;
(*true se a peca pode andar nessa direcao*)
var qx, qy, dif1, dif2: longint;
begin
	//modulo peca, independe de quem eh a vez
	if tab.turno then
		peca:=peca div 10
	else 
		peca:=peca mod 10;
	//testa cada tipo de peca
	case peca of
		//peao ok
		1:testemovimento:=testapeao(j, tab);
		2:begin //torre ok
			if (j.a=j.x) or (j.b=j.y) then
				testemovimento:=true
			else
				testemovimento:=false;
		end;
		3:begin //cavalo ok
			dif1:=abs(j.a-j.x);
			dif2:=abs(j.b-j.y);
			if ((dif1=1) and (dif2=2)) or ((dif1=2) and (dif2=1)) then
				testemovimento:=true
			else
				testemovimento:=false;
		end;
		4:begin //bispo ok
			qx:= abs(j.a-j.x);
			qy:= abs(j.b-j.y);
			if qx = qy then
				testemovimento:=true
			else
				testemovimento:=false;
		end;
		5:begin //rainha ok
			qx:= abs(j.a-j.x);
			qy:= abs(j.b-j.y);
			if (qx = qy) or (j.a=j.x) or (j.b=j.y) then
				testemovimento:=true
			else
				testemovimento:=false;
		end;
		6:begin //rei ok 
			if (abs(j.a-j.x) <= 1) and (abs(j.b-j.y) <= 1) then
				testemovimento:=true
			else
				testemovimento:=false
		else testemovimento:=true;
		end;
	end;
end;


function conferirjogada (j: jogada; tab: tabuleiro): boolean;
(*para conferir precisa saber 
1: se selecionou alguma peca,
	2: se selecionou uma peca da sua cor,
		3: se a jogada c essa peca eh valida
			4: se o destino tem uma peca do time dela mesmo
				5: se nao tem peca no caminho
					6: confere se as jogadas estao dentro do tabuleiro*)

var	peca: integer;	
	ok: boolean;
begin
	ok:=true;
	//6: confeere se nao sai do mapa
	if (j.a < 1) or (j.a > 8) or (j.b < 1) or (j.b > 8) or (j.x < 1) or (j.x > 8) or (j.y < 1) or (j.y > 8) then
		ok:=false;
	if ok then
		peca:=tab.m[j.a,j.b];
	//1: teste se a posicao eh vazia
	if ok and (peca = 0) then
		ok:=false;
	//2: teste se a peca eh sua
	//brancas sao 10, 20, 30..., pretas sao 11, 12, 13...
	if ok and ((((peca mod 10) = 0) and not(tab.turno)) or ((peca mod 10 <> 0) and (tab.turno))) then
		ok:=false;
	//4: teste se ja tem uma peca sua la
	if ok then
		ok:=testelugarocupado(j, tab, peca);
	//3: teste se vc pode fazer esse movimento
	if ok then //a refinar!!!
		ok:=testemovimento(j, peca);
	//5: confere se nao tem peca no caminho
	if ok then
		ok:=testecolisao(j, tab, peca);
	conferirjogada:=ok;
end;


procedure lerjogada (var j: jogada; var tab: tabuleiro);
(*le a jogada ate ela ser valida, confere a validade*)
begin
	repeat
	read(j.a); 
	read(j.b);
	read(j.x);
	read(j.y);
	//confere se isso pode ser feito
	j.validade:=conferirjogada(j, tab);
	if not(j.validade) then
		writeln('JOGADA INVALIDA');
	until j.validade;
	tab.jogadas:=tab.jogadas+1;
end;

procedure atualizar_tabuleiro (j: jogada; var tab: tabuleiro);
begin
	(*passa a peca de posicao e bota um vazio onde estava antes*)
	tab.m[j.x, j.y]:=tab.m[j.a, j.b];
	tab.m[j.a, j.b]:=0;
end;

procedure imprimirtabuleiro (var tab: tabuleiro);
(*passagem normal de matriz, passa as pecas com letras para facilitar leitura
minusculas para brancas e maiusculas para pretas,
alterna o fundo*)
var	i, j: longint; 
	fundo: boolean;
begin
	//inicia branca (fundo = true)
	fundo:=true;
	for i:=1 to 8 do
	begin
		write(' ');
		for j:=1 to 8 do
		begin
			if fundo then 
				begin
				TextBackground(White);
				Textcolor(black);
				end
			else 
			begin
				TextBackground(Black);
				TextColor(white);
			end;
				case tab.m[i,j] of
					0:write('  ');
					10:write('p ');
					20:write('t ');
					30:write('c ');
					40:write('b ');
					50:write('q ');
					60:write('k ');
					11:write('P ');
					12:write('T ');
					13:write('C ');
					14:write('B ');
					15:write('Q ');
					16:write('K ');
				end;
			if j <> 8 then //se for a ultima casa nao alterna
				fundo:=not(fundo);
			TextBackground(black);
		end;
		writeln;
	end;
	//volta ao normal
	TextBackground(Black);
	Textcolor(white);
end;

function fim_de_jogo (j: jogada; tab: tabuleiro): boolean;
(*retorna true se o jogo acabou, mate etc.*)
begin
	//num sei kakakakakak
	fim_de_jogo:=false;
end;

procedure mensagem (var tab: tabuleiro);
(*avisa oq caralhos esta acontecendo*)
begin
	if tab.fim then ,çsç, ç,fv{{{{{{{{{{{{{{{{{{{{{{{{{{(((((((({{{{{{{({({(({({({({({([[[[[[[]]]]]]])})})})})}))})})}}}}}}}))))))))}}}}}}}}}}}}}}}}}}}}}}}}}}
		 /efçmvojernvmswriteln('FIM')
	s
	else
	begin
	writeln('Jogadas: ', tab.jogadas);
		writeln('Vez das brancas')
	else
		writeln('Vez das pretas');
	end;
end;

begin
	criartabuleiro(tab);
	mensagem(tab);
	imprimirtabuleiro(tab);
	(*inicia o jogo. Por enquanto nao tem fim, forcar saida com input invalido (string)*)
	repeat
		lerjogada(j, tab);
		atualizar_tabuleiro(j, tab);
		tab.fim:= fim_de_jogo(j, tab);
		tab.turno:=not(tab.turno);	
		imprimirtabuleiro(tab);
		mensagem(tab);	
	until tab.fim;
end.
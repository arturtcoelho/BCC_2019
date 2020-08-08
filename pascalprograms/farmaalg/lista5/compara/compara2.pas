program compara;
var
	iguais, inverso:boolean;
	i, n, tamA, tamB:integer;
	A, B, C : array [1..100] of integer;

begin
	read(n);
	i:=1;
	while n<>0 do
		begin
		A[i]:=n;
		i:=i+1;
		read(n);
		end;
	tamA:=i-1;
	read(n);
	i:=1;
	while n<>0 do
		begin
		B[i]:=n;
		i:=i+1;
		read(n);
		end;
	tamB:=i-1;
	writeln(tamB);
	inverso:=true;
	i:=1;
	if tamA=tamB then
		begin
		while i<>tamA do
		begin
			if A[i]<>B[tamB] then
				inverso:=false;
			i:=i+1;
			tamB:=tamB-1;
		end;
		if inverso=true then
			writeln('Sim')
		else
			writeln('Nao')
		end
	else
		writeln('Tamanhos diferentes');	
end.

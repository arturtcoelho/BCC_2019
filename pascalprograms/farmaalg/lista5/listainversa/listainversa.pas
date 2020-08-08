program listainversa;
var
i, n, tamA, tamB: integer;
A, B: array [1..100] of integer;
begin
	i:=1;
	read(n);
	tamA:=0;
	tamB:=0;
	(*leitura lista A*)
	while n<>0 do
		begin
		A[i]:=n;
		i:=i+1;
		tamA:=tamA+1;
		read(n);
		end;
	i:=1;
	n:=0;
	(*leitura lista B*)
	read(n);
	while n<>0 do
		begin
		B[i]:=n;
		i:=i+1;
		tamB:=tamB+1;
		read(n);
		end;
	i:=0;
	(*impressao lista A*)
	for i:=tamA downto 1 do
		write(A[i]);
	writeln('');
	for i:=tamB downto 1 do
		write(B[i]);
	writeln('');
end.

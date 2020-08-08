program fibonacci;
var
	n1, n2, n3: qword;
begin
n1	:= 1;
n2	:= 1;
n3	:= (n1 + n2);
writeln (n1);
writeln (n2);
	while n3 < 1844674407370955161 do
(*up to 89th *)
	begin
		writeln (n3);
		n1:= (n3 + n2);
		writeln (n1);
		n2:= (n1 + n3);
		writeln (n2);
		n3:= (n2 + n1); 	
	end;
end.

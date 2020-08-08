program monica;

var i1, i2, i3, im: longint;
begin
	read(im, i1, i2);
	i3:=im-(i1+i2);
	if (i3 > i2) and (i3 > i2) then
		writeln(i3)
	else
	if i2 > i1 then
		writeln(i2)
	else
		writeln(i1);	
end.
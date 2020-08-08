program kmtomiles;
var kmh, mlh:real;
begin
read(kmh);
mlh:= kmh/1.609344;
writeln(mlh:0:4, ' ml/h');
end.

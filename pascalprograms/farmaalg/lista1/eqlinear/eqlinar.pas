program eqlinear;
var
b2o, c2o, a2o, a1, b1, c1, a2, b2, c2, x, y:real;

begin
read(a1, b1, c1, a2, b2, c2);

a2o:=a2;
b2o:=b2;
c2o:=c2;

a2:=(a1*a2);
b2:=(a1*b2);
c2:=(a1*c2);

a1:=(a2o*a1);
b1:=(a2o*b1);
c1:=(a2o*c1);

y:=(c1-c2)/(b1-b2);

x:=(c2o-(b2o*y))/a2o;

writeln('x=', x:0:3);
writeln('y=', y:0:3);

end.

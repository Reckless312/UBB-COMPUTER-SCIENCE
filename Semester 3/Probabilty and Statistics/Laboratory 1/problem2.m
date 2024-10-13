x=0:0.1:3;
plot(x, (x.^5)/10, "-;(x^5)/10;", x, x.*sin(x), "--;x*sin(x);", x, cos(x), ":;cos(x);");
subplot(3,1,1);
plot(x, (x.^5)/10)
subplot(3,1,2);
plot(x, x.*sin(x));
subplot(3,1,3);
plot(x, cos(x));
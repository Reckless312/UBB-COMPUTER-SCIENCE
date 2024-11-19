n = input("Insert value for n bigger or equal to 30: ");
p = input("Insert value for p less or equal to 0,05: ");

x = 0:n;

B = binopdf(x, n, p);

plot(x, B, "r.");

hold on;
P = poisspdf(x, n*p);

plot(x, P, "g--");

p = input("Insert a value for p between 0.05 and 0.95: ");

for n = 1:5:150
  k = 0: n;
  px = binopdf(k, n, p);
  plot(k,px,"r*");
  pause(0.5);
endfor

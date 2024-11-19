p = input("Give a pb p:");
N = input("Give nr of sim N: ");
X = zeros(1, N);
for i = 1:N
  X(i) = 0;
  while rand>=p;
    X(i) = X(i) + 1;
  endwhile
endfor
k = 0:100;
pk = geopdf(k,p);
U_X = unique(X);
n_X = hist(X, length(U_X));
rel_freq = n_X/N;
plot(U_X, rel_freq, "b*", k, pk, "ro");
legend("sum", "geo");


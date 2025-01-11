clear all

p = input("Give a pb p:");
n = input("Give nr of trials n: ");
N = input("Give nr of sim N: ");

X = zeros(n, N);
for i = 1:n
  for j = 1:N
    X(i, j) = 0;
    while rand>=p;
      X(i, j) = X(i, j) + 1;
    endwhile
  endfor
endfor

k = 0:n;
pk = nbinpdf(k,n,p);
U = sum(X);
U_X = unique(U);
n_X = histc(U, U_X);
rel_freq = n_X/N;
plot(U_X, rel_freq, "b*", k, pk, "ro");
legend("sum", "pascal");

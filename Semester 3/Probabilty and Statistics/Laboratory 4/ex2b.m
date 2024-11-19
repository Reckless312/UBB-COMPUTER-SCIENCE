clear all

p = input("Give a pb p:");
n = input("Give nr of trials n: ");
N = input("Give nr of sim N: ");
U = rand(n, N);
X = sum(U < p);
k = 0:n;
pk = binopdf(k, n,p);
U_X = unique(X);
n_X = hist(X, length(U_X));
rel_freq = n_X/N;
plot(U_X, rel_freq, "b*", k, pk, "ro");
legend("sum", "bino");

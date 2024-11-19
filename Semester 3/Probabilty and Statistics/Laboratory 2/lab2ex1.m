clf
n = input("Give number of trials n=");% n - natural number
p = input("Give probability of success p="); % p is in [0, 1]
x = 0:n; % number of successes
px = binopdf(x, n, p);
plot(x, px, 'r*')
hold on
xx = 0:0.01:n;% simulate cont for cdf
cx = binocdf(xx, n, p);
plot(xx, cx, 'b');
legend('pdf','cdf')

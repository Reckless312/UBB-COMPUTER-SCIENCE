clf
N = input("Give number of simulations N = ");
U = rand(3,N); %all simulations of 3 coin tosses
Y = (U < 0.5); % 1 - heads, 0 - tails
X = sum(Y); % sum or columns
hist(X)

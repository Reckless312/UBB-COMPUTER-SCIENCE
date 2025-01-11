X = [22.4, 21.7, 24.5, 23.4, 21.6, 23.3, 22.4, 21.6, 24.8, 20.0];
Y = [17.7, 14.8, 19.6, 19.6, 12.1, 14.8, 15.4, 12.6, 14.0, 12.2];

%a)

X_mean = mean(X);
Y_mean = mean(Y);

n1 = length(X);
n2 = length(Y);

confidence_level = input("Give confidence level: ");
alpha = 1 - confidence_level;

student_quantile = tinv(1-alpha/2, n1+n2-2);

s1 = std(X);
s2 = std(Y);

sp_squared = ((n1-1)* power(s1,2) + (n2-1) * power(s1,2))/(n1+n2-2);
sp = sqrt(sp_squared);

difference1 = X_mean - Y_mean - student_quantile * sp * sqrt(1/n1 + 1/n2);
difference2 = X_mean - Y_mean + student_quantile * sp * sqrt(1/n1 + 1/n2);


printf("The CI for the difference of the true means when sigma1 = sigma2 is (%4.3f,%4.3f)\n", difference1, difference2);

%b)

s1_squared = s1*s1;
s2_squared = s2*s2;

c = (s1_squared/n1)/(s1_squared/n1 + s2_squared/n2);
c_squared = c * c;

one_over_n = c_squared/(n1-1) + power(1-c, 2)/(n2-1);

n = 1/one_over_n;

student_quantile_b = tinv(1-alpha/2, n);

difference1_b = X_mean - Y_mean - student_quantile_b * sqrt(s1_squared/n1 + s2_squared/n2);
difference2_b = X_mean - Y_mean + student_quantile_b * sqrt(s1_squared/n1 + s2_squared/n2);


printf("The CI for the difference of the true means when sigma1 != sigma2 is (%4.3f,%4.3f)\n", difference1_b, difference2_b);

%c)

fisher_distribution_1 = finv(1-alpha/2,n1-1,n2-1);
fisher_distribution_2 = finv(alpha/2,n1-1,n2-1);

ratio1 = (1/fisher_distribution_1) * (s1_squared/ s2_squared);
ratio2 = (1/fisher_distribution_2) * (s1_squared/ s2_squared);

printf("The CI for the ration of the variances is (%4.3f,%4.3f)\n", ratio1, ratio2);

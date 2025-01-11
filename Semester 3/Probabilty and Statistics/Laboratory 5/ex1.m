X = [20, 21, 22, 23, 24, 25, 26, 27,...
      2, 1, 3, 6, 5, 9, 2, 2];
Y = [75, 76, 77, 78, 79, 80, 81, 82,...
      3, 2, 2, 5, 8, 8, 1, 1];

printf("The mean of X is %4.3f, the mean of Y is %4.3f\n", mean(X), mean(X));
printf("The variance of X is %4.3f, the variance of Y is %4.3f\n", var(X), var(Y));

cov_X_Y = cov(X,Y);
corrcoef_X_Y = corrcoef(X,Y);

n = length(cov_X_Y);
printf("The covariance for X and Y is ")
for i = 1:2:(n*2)
   printf("(%4.3f, %4.3f) ", cov_X_Y(i), cov_X_Y(i + 1))
endfor
printf("\n")

n = length(corrcoef_X_Y);
printf("The correlation for X and Y is ")
for i = 1:2:(n*2)
   printf("(%4.3f, %4.3f) ", corrcoef_X_Y(i), corrcoef_X_Y(i + 1))
endfor
printf("\n")

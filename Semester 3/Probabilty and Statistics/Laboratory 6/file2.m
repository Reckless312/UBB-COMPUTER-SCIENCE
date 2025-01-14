X = [22.4, 21.7, 24.5, 23.4, 21.6, 23.3, 22.4, 21.6, 24.8, 20.0];
Y = [17.7, 14.8, 19.6, 19.6, 12.1, 14.8, 15.4, 12.6, 14.0, 12.2];

alpha = 0.50;

%H0: variance of population 1 is equal to the variance of population 2
%H1: variance of population 1 is not equal to the variance population 2
% two tailed test

[h, pval, ci, stats] = vartest2(X,Y,'alpha', alpha, 'tail', 'both');

if h == 1
  printf("The value for h is %d, this means we reject H0\n", h)
  printf("The data suggest that the population variances are not equal\n")
else
  printf("The value for h is %d, this means we don't reject H0\n", h)
  printf("The data suggest that the population variances are equal\n")
endif

n1 = length(X);
n2 = length(Y);

quantile_1 = finv(alpha/2, n1-1, n2-1);
quantile_2 = finv(1-alpha/2,n1-1, n2-1);

RR_1 = [-inf, quantile_1];
RR_2 = [quantile_2, +inf];
printf("The rejection region is (%4.3f, %4.3f) U (%4.3f, %4.3f)\n",RR_1, RR_2)
printf("The observed value of the test statistic is %4.3f.\n", stats.fstat);
printf("The p-value of the test is %4.3f.\n", pval);

%b)
%H0: the mean of the gas mileage with premium gasoline is less or equal to the mean of gas mileage with regular gasoline
%H1: the mean of the gas mileage with premium gasoline is bigger than the mean of gas mileage with regular gasoline
%right tail test

if h == 1
  [h_b, pval_b, ci_b, stats_b] = ttest2(X,Y, 'alpha', alpha, 'vartype', 'unequal', 'tail', 'right');
  if h_b == 1
    printf("The value for h_b is %d, we reject H0\n")
    printf("The data suggest that gas mileage is higher on average\n")
  else
    printf("The value for h_b is %d, we don't reject H0\n")
    printf("The data suggest that gas mileage is less or equal on average\n")
  endif
  var1 = var(X);
  var2 = var(Y);
  c = (var1/n1)/((var1/n1)+(var2/n2));
  n = 1/(((c*c)/(n1-1)) + power((1-c),2)/(n2-1));
  quantile_b = tinv(1-alpha,n);
  RR_b = [quantile_b, +inf];
  printf("The rejection region is (%4.3f, %4.3f)\n",RR_b)
  printf("The observed value of the test statistic is %4.3f.\n", stats_b.tstat);
  printf("The p-value of the test is %4.3f.\n", pval_b);
else
  [h_b, pval_b, ci_b, stats_b] = ttest2(X,Y, 'alpha', alpha, 'vartype', 'equal', 'tail', 'right');
  if h_b == 1
    printf("The value for h_b is %d, we reject H0\n")
    printf("The data suggest that gas mileage is higher on average\n")
  else
    printf("The value for h_b is %d, we don't reject H0\n")
    printf("The data suggest that gas mileage is less or equal on average\n")
  endif
  quantile_b = tinv(1-alpha,n1+n2-2);
  RR_b = [quantile_b, +inf];
  printf("The rejection region is (%4.3f, %4.3f)\n",RR_b)
  printf("The observed value of the test statistic is %4.3f.\n", stats_b.tstat);
  printf("The p-value of the test is %4.3f.\n", pval_b);
endif


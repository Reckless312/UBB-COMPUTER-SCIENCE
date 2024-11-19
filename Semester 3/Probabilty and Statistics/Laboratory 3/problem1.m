printf("Choose distribution:\n");
printf("1.Normal distribution\n");
printf("2.Chisquare distribution\n");
printf("3.Fisher distribution\n");
printf("4.Student distribution\n");

answer = input("Answer: ");

if (answer == 1)
  printf("Subpoint a: ");
  P1 = normcdf(0);
  P2 = 1 - P1;
  printf("P(X<=0) = %d | P(X>=0) = %d\n", P1, P2);
  printf("Subpoint b: ");
  P3 = normcdf(1) - normcdf(-1);
  P4 = 1 - P3;
  printf("P(-1 <= X <= 1) = %d | P(X<=-1 or X>=1) = %d\n", P3, P4);
  printf("Subpoint c: \n");
  alpha = input("Input value for alpha between 0 and 1 : ");
  P5 = norminv(alpha);
  printf("The quantile of order alpha is %d\n", P5);
  printf("Subpoint d: \n");
  beta = input("Input value for beta between 0 and 1: ");
  P6 = norminv(1-beta);
  printf("The quantile of order 1-beta is %d\n", P6);
elseif(answer == 2)
  degree_of_freedom = input("Insert degree of freedom: ");
  printf("Subpoint a: ");
  P1 = chi2cdf(0, degree_of_freedom);
  P2 = 1 - P1;
  printf("P(X<=0) = %d | P(X>=0) = %d\n", P1, P2);
  printf("Subpoint b: ");
  P3 = chi2cdf(1,degree_of_freedom) - chi2cdf(-1,degree_of_freedom);
  P4 = 1 - P3;
  printf("P(-1 <= X <= 1) = %d | P(X<=-1 or X>=1) = %d\n", P3, P4);
  printf("Subpoint c: \n");
  alpha = input("Input value for alpha between 0 and 1 : ");
  P5 = chi2inv(alpha, degree_of_freedom);
  printf("The quantile of order alpha is %d\n", P5);
  printf("Subpoint d: \n");
  beta = input("Input value for beta between 0 and 1: ");
  P6 = chi2inv(1-beta, degree_of_freedom);
  printf("The quantile of order 1-beta is %d\n", P6);
elseif(answer == 3)
   degree_of_freedom = input("Insert first degree of freedom: ");
   degree_of_freedom_2 = input("Insert second degree of freedom: ");
  printf("Subpoint a: ");
  P1 = fcdf(0, degree_of_freedom, degree_of_freedom_2);
  P2 = 1 - P1;
  printf("P(X<=0) = %d | P(X>=0) = %d\n", P1, P2);
  printf("Subpoint b: ");
  P3 = fcdf(1,degree_of_freedom, degree_of_freedom_2) - fcdf(-1,degree_of_freedom, degree_of_freedom_2);
  P4 = 1 - P3;
  printf("P(-1 <= X <= 1) = %d | P(X<=-1 or X>=1) = %d\n", P3, P4);
  printf("Subpoint c: \n");
  alpha = input("Input value for alpha between 0 and 1 : ");
  P5 = finv(alpha, degree_of_freedom, degree_of_freedom_2);
  printf("The quantile of order alpha is %d\n", P5);
  printf("Subpoint d: \n");
  beta = input("Input value for beta between 0 and 1: ");
  P6 = finv(1-beta, degree_of_freedom, degree_of_freedom_2);
  printf("The quantile of order 1-beta is %d\n", P6);
elseif(answer == 4)
   degree_of_freedom = input("Insert degree of freedom: ");
  printf("Subpoint a: ");
  P1 = tcdf(0, degree_of_freedom);
  P2 = 1 - P1;
  printf("P(X<=0) = %d | P(X>=0) = %d\n", P1, P2);
  printf("Subpoint b: ");
  P3 = tcdf(1,degree_of_freedom) - tcdf(-1,degree_of_freedom);
  P4 = 1 - P3;
  printf("P(-1 <= X <= 1) = %d | P(X<=-1 or X>=1) = %d\n", P3, P4);
  printf("Subpoint c: \n");
  alpha = input("Input value for alpha between 0 and 1 : ");
  P5 = tinv(alpha, degree_of_freedom);
  printf("The quantile of order alpha is %d\n", P5);
  printf("Subpoint d: \n");
  beta = input("Input value for beta between 0 and 1: ");
  P6 = tinv(1-beta, degree_of_freedom);
  printf("The quantile of order 1-beta is %d\n", P6);
else
  printf("No available option chosen!\n");
endif

% a statistical test - compare past assumption with a present/future assumption
% try to determine wheter Y or N about a characteristic
% H0 - null hyp <- contains what was previously known
%H1 - alt. hyp <- contains new knowledge
% our statistical tests are in the following format
%H0 : a statistical parameter = some known value ( always H0 contains "=")
%H1 : (the same) statisticial parameter < (or > different) (the same) known value
% < - left tailed test, >- right tailed test, =/= -two tailed test
% a statistical parameter is either one of: a pop.mean, a pop.variance,
% difference between two pop.means, rations of 2 pop.variances
x = [7, 7, 4, 5, 9, 9,...
    4, 12, 8, 1, 8, 7,...
    3, 13, 2, 1, 17, 7,...
    12, 5, 6, 2, 1, 13,...
    14, 10, 2, 4, 9, 11,...
    3, 5, 12, 6, 10, 7];
n = length(x);
alpha = input("Give the significance level: ");


%a)
%H0: m = 8.5 ( the case > 8.5 is absorbed here) - the standard is met
%H1: m < 8.5 - the standard is not met
# this is a left-tailed Z-test for the mean when sigma is known

sigma = 5
m0 = 8.5 % observed value of the mean

[h, p, ci, z] = ztest(x, m0, sigma, "alpha", alpha, "tail", "left");

%build the rejection region
zalpha = norminv(alpha, 0, 1);
RR = [-inf zalpha];

if h == 1 % h = 1 -> reject H0, h=0 -> do not reject H0
  printf("The value for h is %d, This means that  we reject H0. \n", h);
  printf("The data suggests that the standard is not met. \n");
else %h = 0
  printf("The value for h is %d, This means that do not reject H0. \n", h);
  printf("The data suggests that the standard is met. \n");
endif
printf("The rejection region is: (%4.3f, %4.3f).\n", RR);
printf("The observed value of the test statistic is %4.3f.\n", z);
printf("The p-value of the test is %4.3f.\n", p);

% 1)b)ttest -> to get the observed value of the test statistic: stats.tstat
% 2)a) vartest2 -> at the end, you get that the vars are equal or are different
% 2)b) ! it depends on a ) ttest or ttest2

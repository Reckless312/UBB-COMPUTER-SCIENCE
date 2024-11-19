%a)X ~ Bino(3,0.5) and it has the distribution
%(0 1 2 3)
%(1/8 3/8 3/8 1/8)
%b) see prev ex
#c) P(x=0)
P1=binopdf(0,3,0.5);
%P(x<>1) = 1 - P(x=1)
P2=1 - binopdf(1,3,0.5);
printf("P(X=0)=%1.6f\n",P1);
printf("p(X<>1)=%1.6f\n",P2);
P3=binocdf(2,3,0.5);
printf("p(X<=2)=%1.6f\n",P3);
%P(X<2) = P(X<=1)
P4 = binocdf(1,3,0.5);
printf("p(X<=1)=%1.6f\n",P4);
%e)P(X>=1) = 1 - P(X<1) = 1 - P(x<=0)
P5 = 1 - binocdf(0, 3, 0.5);
%P(X>1) = 1 - P(x<=1)
P6 = 1 - binocdf(1,3, 0.5);
printf("p(X>=1)=%1.6f\n",P5);
printf("p(X>1)=%1.6f\n",P6);


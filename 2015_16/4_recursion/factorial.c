#include<stdio.h>

int factorial(int n);
int factorial_tenary(int n);
int factorial_tail_r(int n, int big_n);
int factorial_tail(int n);



int main()
{

  int n=10;

  int n_fact=factorial(n);
  printf("%d ",n_fact);

  n_fact=factorial_tenary(n);
  printf("%d ",n_fact);


  n_fact=factorial_tail(n);
  printf("%d ",n_fact);

  printf("\n");

}

int factorial(int n)
{
   if(n<2)
      return 1;

   return n*factorial(n-1);
}

int factorial_tenary(int n)
{
   return (n<2) ? 1 : n*factorial_tenary(n-1);
}

int factorial_tail_r(int n, int big_n)
{
  if(n<2)
    return big_n;

  return factorial_tail_r(n-1,n*big_n);
}

int factorial_tail(int n)
{
  factorial_tail_r(n,1);
}

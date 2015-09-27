#include<stdio.h>


int fib(int n);
int fib_r(int n, int a, int b);

int main()
{

  int n=30;

  printf("F(%d) is %d\n",n,fib(n));

  return 0;
}

int fib_r(int n, int a, int b)
{
   if(n==0)
     return a;
   if(n==1)
     return b;
   if(n==2)
     return a+b;
     
     return fib_r(n-1,b,a+b);

}

int fib(int n)
{
  return fib_r(n,0,1);
}

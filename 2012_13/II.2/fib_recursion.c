#include<stdio.h>

int fib(int n);

int main()
{

  int n=30;

  printf("F(%d) is %d\n",n,fib(n));

  return 0;
}

int fib(int n)
{
  if(n==0||n==1)
    {
      return n;
    }

  return fib(n-1)+fib(n-2);

}

#include<stdio.h>

int fib(int n);

int main()
{

  int n;

  for(n=2;n<=30;n++)
    {
      printf("F(%d) is %d\n",n,fib(n));
    }

  return 0;
}

int fib(int n)
{

  if(n<2)
     return n;
  
  int last=1;
  int old_last=0;

  int i;

  for(i=2;i<=n;i++)
      {
        int temp=last;
        last=last+old_last;
        old_last=temp;
      }

  return last;
  
}

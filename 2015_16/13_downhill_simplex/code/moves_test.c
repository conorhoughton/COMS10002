#include<stdlib.h>
#include<stdio.h>

enum {DIM=4};

#include"moves.c"

double sum(double x[DIM])
{
  double total=0;
  int i;
  for(i=0;i<DIM;i++)
    total+=x[i];

  return total;
}

int main()
{

  double x[DIM]={1,2,3,4};

  double (*fxn)();

  fxn=sum;

  Point* point=make_point(x,fxn);

  printf("%f\n",point->value);
}
  

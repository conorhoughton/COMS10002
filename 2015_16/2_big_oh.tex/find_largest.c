#include<stdio.h>

int search(int a[],int n);

int main()
{

  int i,n;

  printf("How many elements? ");
  scanf("%d",&n);

  int a[n];

  printf("Input %d elements.\n",n);
  for(i=0;i<n;i++)
    scanf("%d",&a[i]);

  int largest=search(a,n);

  printf("the largest element is %d\n",largest);

  return 0;
}

int search(int a[],int n)
{

  int i;
  int best_val=a[0];

  for(i=1;i<n;i++)
    {
      if(a[i]>best_val)
	best_val= a[i];
    }

  return best_val;
}

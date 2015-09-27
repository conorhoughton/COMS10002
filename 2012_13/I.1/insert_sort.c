#include<stdio.h>

void sort(int a[], int n);

int main()
{

  int i,n;

  printf("How many elements? ");
  scanf("%d",&n);

  int a[n];

  printf("Input %d elements.\n",n);
  for(i=0;i<n;i++)
    scanf("%d",&a[i]);

  sort(a,n);

  printf("Sorted.");
  for(i=0;i<n;i++)
      printf(" %d",a[i]); 

  printf("\n");

  return 0;
}

void sort(int a[],int n)
{

  int i,j,this_a;

  for(i=1;i<n;i++)
    {
      this_a=a[i];
      j=i-1;

      while(j>=0&&this_a<a[j])
	{
	  a[j+1]=a[j];
	  j=j-1;
	}

      a[j+1]=this_a;
    }

}
 

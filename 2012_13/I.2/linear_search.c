#include<stdio.h>

void sort(int a[], int n);
int search(int a[], int n, int val);

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

  int val;

  printf("Which element do you want? ");
  scanf("%d",&val);

  int index=search(a,n,val);

  if(index==-1)
    printf("That wasn't an element you eejit!\n");
  else
    printf("In the sorted array %d was element %d\n",val,index);

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
 
int search(int a[],int n, int val)
{

  int i;

  for(i=0;i<n;i++)
    {
      if(a[i]==val)
	return i;
    }

  return -1;
}


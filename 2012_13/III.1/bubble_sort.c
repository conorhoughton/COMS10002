#include<stdio.h>

void bubble(int a[],int n);
void print_array(int a[], int n);
void swap(int a[],int i, int j);

int main()
{

  int n,big_n;

  printf("How many elements? ");
  scanf("%d",&n);

  printf("Largest element? ");
  scanf("%d",&big_n);
  
  int a[n];

  int i;

  for(i=0;i<n;i++)
    a[i]=rand()%big_n;
  
  print_array(a,n);

  bubble(a,n);

  print_array(a,n);


}

void swap(int a[],int i, int j)
{
  int temp=a[i];
  a[i]=a[j];
  a[j]=temp;
}


void bubble(int a[], int n)
{

  int i,unfinished=1;
  
  while(unfinished)
    {
      unfinished=0;
      for(i=0;i<n-1;i++)
	if(a[i]>a[i+1])
	  {
	    unfinished=1;
	    swap(a,i,i+1);	    
	  }
    }

}


void print_array(int a[], int n)
{
  int i;

  for(i=0;i<n;i++)
      printf(" %d",a[i]); 

  printf("\n");

}

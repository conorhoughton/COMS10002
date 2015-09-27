#include<stdio.h>
#include<time.h>

void sort(int a[], int n);

int main()
{

  clock_t begin,end;

  int i,n;
  int n0=1,n1=1000;
  int trials=500;

  for(n=n0;n<n1 ;++n)
    {

      int a[trials][n];
      
      int trial_c;
      
      for(trial_c=0;trial_c<trials;trial_c++)
	for(i=0;i<n;i++)
	  a[trial_c][i]=n-i-1;	

      begin = clock();
      for(trial_c=0;trial_c<trials;trial_c++)
	sort(a[trial_c],n);
      end = clock();

      double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;      

	

      printf("%i %f\n",n,time_spent);

    }

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
 

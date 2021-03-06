//radix_sort.c
//a program to calculate perform radix_sort
//part of the PandA1 course at Bristol University
//2015 Conor Houghton conor.houghton@bristol.ac.uk

//To the extent possible under law, the author has dedicated all copyright 
//and related and neighboring rights to this software to the public domain 
//worldwide. This software is distributed without any warranty. 

#include<stdio.h>
#include<math.h>

void radix_sort(int a[], int n, int a_bound);
void print_array(int a[], int n);

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

  printf("\n");

  radix_sort(a,n,big_n-1);

  print_array(a,n);

}

void radix_sort(int a[], int n, int a_bound)
{

  int exp_max=log10((double)a_bound)+1;

  int a_sort[n];

  int i,exp;

  for(exp=0;exp<exp_max;exp++)
    {
      int buckets[10]={0};
      int digit=pow(10,exp);
      for(i=0;i<n;i++)
	buckets[a[i]/digit%10]++;
      for(i=1;i<10;i++)
	buckets[i]+=buckets[i-1];

      for(i=n-1;i>=0;i--)
	{
	  buckets[a[i]/digit%10]--;
	  a_sort[buckets[a[i]/digit%10]]=a[i];
	}

      for(i=0;i<n;i++)
	a[i]=a_sort[i];

    }

}


void print_array(int a[], int n)
{
  int i;

  for(i=0;i<n;i++)
      printf(" %d",a[i]); 

  printf("\n");

}


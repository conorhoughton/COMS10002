/* this is intended to test the syntax for dealing with passing an
   array of pointers, it does not make a hash_table, but might be
   useful when making one.  */ 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <math.h>
#include <ctype.h>

typedef struct Node{
  int entry;
}node;

node* make_node(int entry)
{
  node *new_node=calloc(1, sizeof(node));
  new_node->entry=entry;
  return new_node;
}

void add_node(node* table[],int index,int entry)
{
 
  if(table[index]!=NULL)
    free(table[index]);

  table[index]=make_node(entry);
}

void print_table(node* table[],int table_size)
{
  for(int i=0;i<table_size;i++)
    if(table[i]!=NULL)
      printf("%i %i",i,table[i]->entry);
}


int main()
{
  int table_size=5;
  
  node* table[table_size];
  for(int i=0;i<table_size;i++)
    table[i]=NULL;

  add_node(table,1,100);
  print_table(table,table_size);


}

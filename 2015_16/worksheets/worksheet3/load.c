#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<ctype.h>
FILE* book;
FILE* output;

typedef struct List 
{
	struct List *next;
	char word[20];
	int count;
} list;

void read(char word[20])
{
	char c;
	if(fscanf(book,"%c",&c)!=EOF)
	  {
		char a[]=". ,;:*!?'-\n\0\r";
		int i;
		i=0;
		while(strchr(a,c)==0)
		{
			word[i]=c;
			i++;
			if(fscanf(book,"%c",&c)==EOF)
				break;
		}
		word[i]='\0';
	  }
	else
	  {
	    strcpy(word,"EOF");
	  }
	    
}

list *insert( char new_word[20], list *B)
{
	list *T=calloc(1, sizeof(list));
	strcpy(T->word,new_word);
	T->count=1;
	T->next=B;
	return T;
}

list *add(list *old_list, char new_word[20])
{

	if(old_list==NULL)
	{
		return insert(new_word,NULL);
	}
	else
	{
		list *new_list;
		for(new_list=old_list;new_list->next!=NULL;new_list=new_list->next)
		{
		}
		new_list->next=insert(new_word,NULL);
		return old_list;
	}
}

int find(list *t_list, char what[20])
{
	for(;t_list!=NULL;t_list=t_list->next)
	{
		if(strcasecmp(what,t_list->word)==0)
		{
			return 1;
		}
	}
	return 0;
}

list *find_word(list *t_list, char word[20], int *steps)
{
	*steps=0;
	for(;t_list!=NULL;t_list=t_list->next)
	{
		*steps=*steps+1;
		if(strcasecmp(word,t_list->word)==0)
		{
			return t_list;
		}
	}
	return 0;
}

list *insertwordlist(list *a_list)
{	
	char word[20];
	int steps,t;
	list *point;
	read(word);
	if (word[0]!='\0'&&word[0]!='\n'&&strcmp(word,"EOF")!=0)
	{
		a_list=add(a_list,word);
	}
	while(strcmp(word,"EOF")!=0)
	{
		read(word);
		if (word[0]!='\0'&&word[0]!='\n'&&strcmp(word,"EOF")!=0)
		{
			
			if(find(a_list,word)==0)
			{
				a_list=add(a_list,word);
				t++;
			}
			else
			{
				point=find_word(a_list,word,&steps);
				point->count++;
			}	
		}
	}
	
	return a_list;
}

int main(int argc,char *argv[])
{
	list *linked_list;
	linked_list=NULL;
		
	book=fopen(argv[1],"r");
	clock_t start=clock();
	linked_list=insertwordlist(linked_list);		
	clock_t stop=clock();
	fclose(book);
	
	double time_taken=(stop-start)/CLOCKS_PER_SEC;

	printf("%f\n",time_taken);

	printf("%i\n",find(linked_list,"cow"));
	printf("%i\n",find(linked_list,"computer"));

	return 0;
}	

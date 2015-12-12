#include<stdlib.h>
#include<stdio.h>
#include<math.h>


enum{DIM=2};

#include "latex_triangles.c"
#include "downhill_simplex.c"

double quad(double x[DIM])
{
  double total=0;
  int i;
  for(i=0;i<DIM;i++)
    total+=pow(x[i],2);

  return total;
}

//p5 http://www.geatbx.com/download/GEATbx_ObjFunExpl_v38.pdf
//scaled
double hyper_ellipsoid(double x[DIM])
{
  double total=0;
  int i;
  for(i=0;i<DIM;i++)
    total+=(i+1)*pow(x[i]/5.0,2);

  return total;
}

int main()
{
  double (*fxn)();
  fxn=hyper_ellipsoid;

  Point* points[DIM];

  double x[DIM]={10,10};
  double epsilon=0.5;

  make_points(x,epsilon,fxn,points);
  
  print_point(points[0]);
  print_point(points[1]);
  print_point(points[2]);
  
  int step_c,step_n=100;

  Point *xo=malloc(sizeof(Point));
  Point *xr=malloc(sizeof(Point));
  Point *xc=malloc(sizeof(Point));
  Point *xe=malloc(sizeof(Point));

  int best,worst;
  double best_value,worst_value;

  char move='s';

  FILE * output_file;
  output_file=fopen("triangles.tex","w");

  make_preamble(output_file);

  for(step_c=0;step_c<step_n;step_c++)
    {
      best_and_worst(points,&best,&worst);
      best_value=points[best]->value;
      worst_value=points[worst]->value;

      set_centroid(points,worst,xo);

      set_reflected(xo,points[worst],fxn,xr);

      if(xr->value<best_value)
	{
	  set_extended(xo,points[worst],fxn,xe);
	  if(xe->value<xr->value)
	    {
	      copy_value(xe,points[worst]);
	      move='e';
	    }
	  else
	    {
	      copy_value(xr,points[worst]);
	      move='r';
	    }
	}
      else if(xr->value<worst_value)
	{
	  copy_value(xr,points[worst]);
	  move='r';
	}
      else
	{
	  set_contracted(xo,points[worst],fxn,xc);
	  if(xc->value<worst_value)
	    {
	      copy_value(xc,points[worst]);
	      move='c';
	    }
	  else
	    {
	      reduce(points,best,fxn);
	      move='d';

	    }
	  
	}

      printf("\n");
      print_point(points[0]);
      print_point(points[1]);
      print_point(points[2]);
      printf("%c(%f)",move,best_value);	  
     
      add_centered_triangle(output_file,points[0]->x,points[1]->x,points[2]->x);


    }
  printf("\n");

  
  make_postamble(output_file);

  fclose(output_file);

}

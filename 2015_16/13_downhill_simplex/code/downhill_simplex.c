


struct Point
{
  double value;
  double x[DIM];
};

typedef struct Point Point;

void print_point(Point* point)
{
  int i;
  for(i=0;i<DIM;i++)
    printf("%f ",(point->x)[i]);
  printf(" : %f\n",point->value);
}

Point* make_point(double this_x[DIM],double (*fxn)())
{
  Point*  point=malloc(sizeof(Point));
  int i=0;
  for(i=0;i<DIM;i++)
    (*point).x[i]=this_x[i];

  point->value=(*fxn)(this_x);

  return point;
}

void set_centroid(Point* points[DIM+1],int worst,Point* centroid)
{
  double center[DIM];
  
  int i,j;

  for(i=0;i<DIM;i++)
    center[i]=0.0;

  for(i=0;i<DIM+1;i++)
    if(i!=worst)
      for(j=0;j<DIM;j++)
	center[j]+=(points[i])->x[j];
 
  for(i=0;i<DIM;i++)
    {
      center[i]/=DIM;
      (centroid->x)[i]=center[i];
    }

  centroid->value=0;
}

void set_polated_point(Point* centroid,Point* worst,double(*fxn)(),double lambda, Point* pol_point)
{
  double pol_position[DIM];
  
  int i;

  for(i=0;i<DIM;i++)
    pol_position[i]=(centroid->x)[i]+lambda*((centroid->x)[i]-(worst->x)[i]);
  
  for(i=0;i<DIM;i++)
    (pol_point->x)[i]=pol_position[i];

  pol_point->value=(*fxn)(pol_position);

}

void set_reflected(Point* centroid,Point* worst,double(*fxn)(), Point* ref_point)
{
  set_polated_point(centroid,worst,fxn,1.0,ref_point);
}


void set_extended(Point* centroid,Point* worst,double(*fxn)(), Point* ext_point)
{
  set_polated_point(centroid,worst,fxn,2.0,ext_point);
}


void set_contracted(Point* centroid,Point* worst,double(*fxn)(), Point* con_point)
{
  set_polated_point(centroid,worst,fxn,-0.5,con_point);
}

void reduce(Point* points[DIM],int best,double(*fxn)())
{

  int i,j;
  double x;

  for(j=0;j<DIM;j++)
    {
      x=((points[best])->x)[j];
      for(i=0;i<DIM+1;i++)
	if(i!=best)
	  {
	    ((points[i])->x)[j]=0.5*(((points[i])->x)[j]+x);
	  }
    }


  for(i=0;i<DIM+1;i++)
    if(i!=best)
      (points[i])->value=(*fxn)((points[i])->x);
}
      


void best_and_worst(Point* points[DIM+1],int *best,int *worst)
{
  *best=0;
  double best_val=points[0]->value;
  *worst=1;
  double worst_val=points[1]->value;

  if(worst_val<best_val)
    {
      best_val=worst_val;
      *best=0;
      worst_val=points[0]->value;
      *worst=1;
    }

  int i;
  double this_val;

  for(i=2;i<DIM;i++)
    {
      this_val=points[i]->value;
      if(this_val>worst_val)
	{
	  worst_val=this_val;
	  *worst=i;
	}
      else if(this_val<best_val)
	{
	  best_val=this_val;
	  *best=i;
	}

    }
}

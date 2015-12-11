
struct Point
{
  double x[DIM];
  double value;
};

typedef struct Point Point;

Point* make_point(double this_x[DIM],double (*fxn)())
{
  Point*  point=malloc(sizeof(Point));
  int i=0;
  for(i=0;i<DIM;i++)
    (*point).x[i]=this_x[i];

  point->value=(*fxn)(this_x);

  return point;
}

/*
Point* reflection(Point * center_of_mass,Point * worst)
{
  Point* reflected_point;
}
*/



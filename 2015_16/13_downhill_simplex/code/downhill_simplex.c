
enum{SIZE=4};



struct Point
{
  double value;
  double x[SIZE];
} Point;

Point* make_point(int dim,double this_x[SIZE],double this_value)
{
  Point* new_point=(point *)malloc(sizeof(Point));
  new_point->x=this_x;
  new_point->value=this_value;

  return new_point;
}

Point* 
  
  

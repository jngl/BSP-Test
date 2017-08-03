#include "base.hpp"

#include <cmath>

Vector2f getNormal(Vector2f a, Vector2f b)
{
  Vector2f Normal;
  Normal.x = a.y - b.y;
  Normal.y = b.x - a.x;
  
  float Len = sqrt(Normal.x * Normal.x + Normal.y * Normal.y);
  if (Len == 0.f)
    return Normal;
  
  Normal.x /= Len;
  Normal.y /= Len;
  
  return Normal;
}

float Determinant(Vector2f a, Vector2f b)
{
  return a.x*b.y-a.y*b.x;
}

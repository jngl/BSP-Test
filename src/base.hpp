#ifndef BASE_H
#define BASE_H

template<class T>
struct Vector2
{
  T x;
  T y;

  Vector2<T>& operator/=(const T& rhs){
    x/=rhs;
    y/=rhs;
    return *this;
  }
  
};

template<class T>
Vector2<T> operator-(Vector2<T> a, Vector2<T> b){
  return {a.x-b.x, a.y-b.y};
}

template<class T>
Vector2<T> operator+(Vector2<T> a, Vector2<T> b){
  return {a.x+b.x, a.y+b.y};
}

template<class T>
Vector2<T> operator*(Vector2<T> a, T b){
  return {a.x*b, a.y*b};
}

typedef Vector2<float> Vector2f;

Vector2f getNormal(Vector2f a, Vector2f b);

float Determinant(Vector2f a, Vector2f b);

#endif

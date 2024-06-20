#include "Vector3D.hpp"
#include <cmath>

// iloczyn wektorowy
template <class T>
Vector3D<T> Vector3D<T>::calculateCrossProduct(const Vector3D<T>& v) const
{
  const auto x = getY() * v.getZ() - getZ() * v.getY();
  const auto y = getZ() * v.getX() - getX() * v.getZ();
  const auto z = getX() * v.getY() - getY() * v.getX();

  return Vector3D<T>(Vertex3D<T>(x, y, z));
}

template <class T>
Vector3D<T> Vector3D<T>::normalize(int normalizedVectorLength) const
{
  const auto len = length();

  T x = 0;
  T y = 0;
  T z = 0;
  
  if (len != 0)
  {
    x = getX() * normalizedVectorLength / len;
    y = getY() * normalizedVectorLength / len;
    z = getZ() * normalizedVectorLength / len;
  }
  
  return Vector3D<T>(Vertex3D<T>(x, y, z));
}

template class Vector3D<short>;
template class Vector3D<int>;

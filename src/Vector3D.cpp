#include "Vector3D.hpp"
#include <cmath>

// iloczyn wektorowy
Vector3D Vector3D::CrossProduct(const Vector3D& v) const
{
  const short x = getY() * v.getZ() - getZ() * v.getY();
  const short y = getZ() * v.getX() - getX() * v.getZ();
  const short z = getX() * v.getY() - getY() * v.getX();

  return Vector3D({x, y, z});
}

Vector3D Vector3D::Normalize(int normalizedVectorLength) const
{
  const double len = length();

  short x = 0;
  short y = 0;
  short z = 0;
  
  if (len != 0)
  {
    x = getX() * normalizedVectorLength / len;
    y = getY() * normalizedVectorLength / len;
    z = getZ() * normalizedVectorLength / len;
  }
  
  return Vector3D({x, y, z});
}


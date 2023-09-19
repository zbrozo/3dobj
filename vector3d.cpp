#include "vector3d.hpp"
#include <cmath>

Vector3d Vector3d::CrossProduct(const Vector3d& v) const
{
  auto newX = y * v.z - z * v.y;
  auto newY = z * v.x - x * v.z;
  auto newZ = x * v.y - y * v.x;

  return Vector3d(newX, newY, newZ);
}

Vector3d Vector3d::Normalize() const
{
  const double len = sqrt(x * x + y * y + z * z);

  short x2 = 0;
  short y2 = 0;
  short z2 = 0;
  
  if (len != 0)
    {
      const short normalizedVectorLength = 32;
      x2 = x * normalizedVectorLength / len;
      y2 = y * normalizedVectorLength / len;
      z2 = z * normalizedVectorLength / len;
    }

  return Vector3d(x2, y2, z2);
}


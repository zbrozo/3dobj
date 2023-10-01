#include "vector3d.hpp"
#include <cmath>

// iloczyn wektorowy
Vector3d Vector3d::CrossProduct(const Vector3d& v) const
{
  const auto newX = mY * v.mZ - mZ * v.mY;
  const auto newY = mZ * v.mX - mX * v.mZ;
  const auto newZ = mX * v.mY - mY * v.mX;

  return Vector3d(newX, newY, newZ);
}

Vector3d Vector3d::Normalize() const
{
  const double len = sqrt(mX * mX + mY * mY + mZ * mZ);

  short x = 0;
  short y = 0;
  short z = 0;
  
  if (len != 0)
    {
      const short normalizedVectorLength = 64;
      x = mX * normalizedVectorLength / len;
      y = mY * normalizedVectorLength / len;
      z = mZ * normalizedVectorLength / len;
    }

  return Vector3d(x, y, z);
}


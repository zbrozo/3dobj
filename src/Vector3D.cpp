#include "Vector3D.hpp"
#include <cmath>

// iloczyn wektorowy
Vector3D Vector3D::CrossProduct(const Vector3D& v) const
{
  const auto newX = mY * v.mZ - mZ * v.mY;
  const auto newY = mZ * v.mX - mX * v.mZ;
  const auto newZ = mX * v.mY - mY * v.mX;

  return Vector3D(newX, newY, newZ);
}

Vector3D Vector3D::Normalize(int normalizedVectorLength) const
{
  const double len = sqrt(mX * mX + mY * mY + mZ * mZ);

  short x = 0;
  short y = 0;
  short z = 0;
  
  if (len != 0)
  {
    x = mX * normalizedVectorLength / len;
    y = mY * normalizedVectorLength / len;
    z = mZ * normalizedVectorLength / len;
  }
  
  return Vector3D(x, y, z);
}


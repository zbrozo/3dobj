#include "vector3d.hpp"
#include <cmath>

void Vector3d::Normalize()
{
  const double len = sqrt(x * x + y * y + z * z);
  if (len != 0)
    {
      const short normalizedVectorLength = 32;
      x = x * normalizedVectorLength / len;
      y = y * normalizedVectorLength / len;
      z = z * normalizedVectorLength / len;
    }
}

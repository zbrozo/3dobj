#include "face.hpp"
#include "vertex.hpp"
#include "vector3d.hpp"
#include <cmath>

Vector3d Face::CalculateNormalVector(const std::vector<Vertex>& vertices,
                                     const Face& face)
{
  //  std::cout << __FUNCTION__ << "\n";

  // wyznaczenie wektora wypadkowego do ściany
  
  auto v1 = face[0];
  auto v2 = face[1];
  auto v3 = face[2];

  auto x1 = vertices[v2].x - vertices[v1].x;
  auto y1 = vertices[v2].y - vertices[v1].y;
  auto z1 = vertices[v2].z - vertices[v1].z;
  
  auto x2 = vertices[v3].x - vertices[v1].x;
  auto y2 = vertices[v3].y - vertices[v1].y;
  auto z2 = vertices[v3].z - vertices[v1].z;
  
  auto x = (y1 * z2 - z1 * y2);
  auto y = (z1 * x2 - x1 * z2);
  auto z = (x1 * y2 - y1 * x2);

  Vector3d vector(x, y, z);
  vector.Normalize();
  
  /*
  const double len = sqrt(x * x + y * y + z * z);

  if (len != 0)
    {
      const short normalizedVectorLength = 60;
      x = x * normalizedVectorLength / len;
      y = y * normalizedVectorLength / len;
      z = z * normalizedVectorLength / len;
    }
  
  Vertex vertex(x, y, z);
  */

  
  //std::cout << x << ", " << y << ", " << z << "\n";
  
  return vector;
}

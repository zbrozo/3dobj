#include "rotation.hpp"
#include <cmath>

#define PI 3.14159265
#define radian (PI / 180.0)

Vertex Rotation::rotateX(Vertex vertex, int d)
{
  Vertex result;
  result.x = vertex.x;
  result.y = vertex.y * cos(d * radian) - vertex.z * sin(d * radian);
  result.z = vertex.y * sin(d * radian) + vertex.z * cos(d * radian);
  return result;
}

Vertex Rotation::rotateY(Vertex vertex, int d)
{
  Vertex result;
  result.x = vertex.x * cos(d * radian) + vertex.z * sin(d * radian);
  result.y = vertex.y;
  result.z = vertex.z * cos(d * radian) - vertex.x * sin(d * radian);
  return result;
}

Vertex Rotation::rotateZ(Vertex vertex, int d)
{
  Vertex result;
  result.x = vertex.x * cos(d * radian) - vertex.y * sin(d * radian);
  result.y = vertex.x * sin(d * radian) + vertex.y * cos(d * radian);
  result.z = vertex.z;
  return result;
}

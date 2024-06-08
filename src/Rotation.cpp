#include "Rotation.hpp"
#include <cmath>

#define PI 3.14159265
#define radian (PI / 180.0)

Vertex Rotation::rotateX(Vertex vertex, int d)
{
  Vertex result;
  result.mX = vertex.mX;
  result.mY = vertex.mY * cos(d * radian) - vertex.mZ * sin(d * radian);
  result.mZ = vertex.mY * sin(d * radian) + vertex.mZ * cos(d * radian);
  return result;
}

Vertex Rotation::rotateY(Vertex vertex, int d)
{
  Vertex result;
  result.mX = vertex.mX * cos(d * radian) + vertex.mZ * sin(d * radian);
  result.mY = vertex.mY;
  result.mZ = vertex.mZ * cos(d * radian) - vertex.mX * sin(d * radian);
  return result;
}

Vertex Rotation::rotateZ(Vertex vertex, int d)
{
  Vertex result;
  result.mX = vertex.mX * cos(d * radian) - vertex.mY * sin(d * radian);
  result.mY = vertex.mX * sin(d * radian) + vertex.mY * cos(d * radian);
  result.mZ = vertex.mZ;
  return result;
}

#include "Rotation.hpp"
#include <cmath>

#define PI 3.14159265
#define radian (PI / 180.0)

template<class T>
T Rotation3D<T>::rotateX(T coord, int d)
{
  T result;
  result.mX = coord.mX;
  result.mY = coord.mY * cos(d * radian) - coord.mZ * sin(d * radian);
  result.mZ = coord.mY * sin(d * radian) + coord.mZ * cos(d * radian);
  return result;
}

template<class T>
T Rotation3D<T>::rotateY(T coord, int d)
{
  T result;
  result.mX = coord.mX * cos(d * radian) + coord.mZ * sin(d * radian);
  result.mY = coord.mY;
  result.mZ = coord.mZ * cos(d * radian) - coord.mX * sin(d * radian);
  return result;
}

template<class T>
T Rotation3D<T>::rotateZ(T coord, int d)
{
  T result;
  result.mX = coord.mX * cos(d * radian) - coord.mY * sin(d * radian);
  result.mY = coord.mX * sin(d * radian) + coord.mY * cos(d * radian);
  result.mZ = coord.mZ;
  return result;
}

template class Rotation3D<Vertex>;

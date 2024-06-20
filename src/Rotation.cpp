#include "Rotation.hpp"

#include <type_traits>
#include <cmath>

#define PI 3.14159265
#define radian (PI / 180.0)

template<class T>
T Rotation3D<T>::rotateX(T coord, int d)
{
  const int x = coord.getX();
  const int y = coord.getY() * cos(d * radian) - coord.getZ() * sin(d * radian);
  const int z = coord.getY() * sin(d * radian) + coord.getZ() * cos(d * radian);
  return Vertex(x, y, z);
}

template<class T>
T Rotation3D<T>::rotateY(T coord, int d)
{
  const int x = coord.getX() * cos(d * radian) + coord.getZ() * sin(d * radian);
  const int y = coord.getY();
  const int z = coord.getZ() * cos(d * radian) - coord.getX() * sin(d * radian);
  return Vertex(x, y, z);
}

template<class T>
T Rotation3D<T>::rotateZ(T coord, int d)
{
  const int x = coord.getX() * cos(d * radian) - coord.getY() * sin(d * radian);
  const int y = coord.getX() * sin(d * radian) + coord.getY() * cos(d * radian);
  const int z = coord.getZ();
  return Vertex(x, y, z);
}

template class Rotation3D<Vertex>;
template class Rotation3D<Vector>;

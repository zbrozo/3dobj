#include "Rotation.hpp"
#include <cmath>

namespace
{

template <typename T> constexpr T pi = T(3.14159265);
template <typename T> constexpr T radian = T(pi<T> / 180.0);

auto getRadian(int degree)
{
  return degree * radian<double>;
}

} // namespace

template<class T>
T Rotation3D<T>::rotateX(T coord, int d)
{
  const int x = coord.getX();
  const int y = coord.getY() * cos(getRadian(d)) - coord.getZ() * sin(getRadian(d));
  const int z = coord.getY() * sin(getRadian(d)) + coord.getZ() * cos(getRadian(d));
  return Vertex(x, y, z);
}

template<class T>
T Rotation3D<T>::rotateY(T coord, int d)
{
  const int x = coord.getX() * cos(getRadian(d)) + coord.getZ() * sin(getRadian(d));
  const int y = coord.getY();
  const int z = coord.getZ() * cos(getRadian(d)) - coord.getX() * sin(getRadian(d));
  return Vertex(x, y, z);
}

template<class T>
T Rotation3D<T>::rotateZ(T coord, int d)
{
  const int x = coord.getX() * cos(getRadian(d)) - coord.getY() * sin(getRadian(d));
  const int y = coord.getX() * sin(getRadian(d)) + coord.getY() * cos(getRadian(d));
  const int z = coord.getZ();
  return Vertex(x, y, z);
}

template class Rotation3D<Vertex>;
template class Rotation3D<Vector>;

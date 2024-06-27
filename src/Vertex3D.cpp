#include "Vertex3D.hpp"

template<class T>
Vertex3D<T> Vertex3D<T>::operator+(const Vertex3D<T>& v) const
{
  return Vertex3D<T>(mX + v.mX, mY + v.mY, mZ + v.mZ);
}

template<class T>
Vertex3D<T>& Vertex3D<T>::operator+=(const Vertex3D<T>& v)
{
  mX += v.mX;
  mY += v.mY;
  mZ += v.mZ;
  return *this;
}

template<class T>
bool Vertex3D<T>::operator==(const Vertex3D<T>& v) const
{
  return (mX == v.mX && mY == v.mY && mZ == v.mZ);
}

template<typename T>
Vertex3D<T> Vertex3D<T>::operator*(T value) const
{
  return Vertex3D<T>(mX * value, mY * value, mZ * value);
}

template<typename T>
Vertex3D<T> Vertex3D<T>::operator/(T value) const
{
  Vertex3D<T> vertex(mX / value, mY / value, mZ / value);

  auto rounding = [value](T pos, T& result)
  {
    if (abs(pos % value) >= (value / 2))
    {
      result += result < 0 ? -1 : 1;
    }
  };

  rounding(mX, vertex.mX);
  rounding(mY, vertex.mY);
  rounding(mZ, vertex.mZ);

  return vertex;
}

template class Vertex3D<short>;
template class Vertex3D<int>;


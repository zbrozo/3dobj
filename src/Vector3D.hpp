#pragma once
#include "Vertex3D.hpp"
#include <cmath>
#include <ostream>

template<typename T>
class Vector3D
{
  Vertex3D<T> mBegin = {0,0,0};
  Vertex3D<T> mEnd = {0,0,0};
  
public:

  Vector3D() {}

  Vector3D(Vertex3D<T> end) :
    mBegin({0,0,0}), mEnd(end)
  {
  }
  
  Vector3D(Vertex3D<T> begin, Vertex3D<T> end) :
    mBegin(begin), mEnd(end)
  {
  }

  virtual ~Vector3D() = default;

  Vector3D(const Vector3D&) = default;
  Vector3D(Vector3D &&) = default;
  Vector3D& operator=(const Vector3D& v) = default;
  Vector3D& operator=(Vector3D &&) = default;

  bool operator==(const Vector3D& vector) const
  {
    return getX() == vector.getX() && getY() == vector.getY() && getZ() == vector.getZ();
  }

  Vertex3D<T> getBegin() const
  {
    return mBegin;
  }

  Vertex3D<T> getEnd() const
  {
    return mEnd;
  }
  
  T getX() const
  {
    return mEnd.getX() - mBegin.getX();
  }

  T getY() const
  {
    return mEnd.getY() - mBegin.getY();
  }

  T getZ() const
  {
    return mEnd.getZ() - mBegin.getZ();
  }

  int length() const
  {
    const auto x = getX();
    const auto y = getY();
    const auto z = getZ();
    return sqrt(x * x + y * y + z * z);
  }
  
  Vector3D calculateCrossProduct(const Vector3D& v) const;
  Vector3D normalize(int normalizedVectorLength = 64) const;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector3D<T>& vector)
{
  os << "[" << vector.getX()  << ", " << vector.getY() << ", " << vector.getZ() << "]";
  return os;
}

#pragma once
#include "Vertex3D.hpp"
#include <cmath>

class Vector3D
{
  Vertex3D<short> mBegin = {0,0,0};
  Vertex3D<short> mEnd = {0,0,0};
  
public:

  Vector3D() {}

  Vector3D(Vertex3D<short> end) :
    mBegin({0,0,0}), mEnd(end)
  {
  }
  
  Vector3D(Vertex3D<short> begin, Vertex3D<short> end) :
    mBegin(begin), mEnd(end)
  {
  }

  virtual ~Vector3D() = default;

  Vector3D(const Vector3D&) = default;
  Vector3D(Vector3D &&) = default;
  Vector3D& operator=(const Vector3D& v) = default;
  Vector3D& operator=(Vector3D &&) = default;

  Vertex3D<short> getBegin() const
  {
    return mBegin;
  }

  Vertex3D<short> getEnd() const
  {
    return mEnd;
  }
  
  short getX() const
  {
    return mEnd.getX() - mBegin.getX();
  }

  short getY() const
  {
    return mEnd.getY() - mBegin.getY();
  }

  short getZ() const
  {
    return mEnd.getZ() - mBegin.getZ();
  }

  short length() const
  {
    const auto x = getX();
    const auto y = getY();
    const auto z = getZ();
    return sqrt(x * x + y * y + z * z);
  }
  
  Vector3D CrossProduct(const Vector3D& v) const;
  Vector3D Normalize(int normalizedVectorLength = 64) const;
};

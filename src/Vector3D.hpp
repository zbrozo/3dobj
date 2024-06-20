#pragma once
#include "Vertex3D.hpp"

class Vector3D : public Vertex3D<short>
{
public:

  Vector3D() {}
  
  Vector3D(short x, short y, short z) :
    Vertex3D(x,y,z) //mX(x), mY(y), mZ(z)
  {
  }

  virtual ~Vector3D() = default;

  Vector3D(const Vector3D&) = default;
  Vector3D(Vector3D &&) = default;
  Vector3D& operator=(const Vector3D& v) = default;
  Vector3D& operator=(Vector3D &&) = default;

  Vector3D(const Vertex3D<short>& vertex)
  {
    mX = vertex.mX;
    mY = vertex.mY;
    mZ = vertex.mZ;
  }
  
  Vector3D CrossProduct(const Vector3D& v) const;
  Vector3D Normalize(int normalizedVectorLength = 64) const;
};

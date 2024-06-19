#pragma once
#include "Vertex.hpp"

class Vector3d : public Vertex
{

public:

  Vector3d(short _x, short _y, short _z) :
    Vertex(_x, _y, _z)
  {
  }

  Vector3d(Vertex v) :
    Vertex(v)
  {
  }

  virtual ~Vector3d() = default;

  Vector3d(Vector3d const &) = default;
  Vector3d(Vector3d &&) = default;
  Vector3d& operator=(const Vector3d& v) = default;
  Vector3d& operator=(Vector3d &&) = default;

  Vector3d CrossProduct(const Vector3d& v) const;
  Vector3d Normalize() const;
};

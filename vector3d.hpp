#pragma once
#include "vertex.hpp"

class Vector3d : public Vertex
{

public:

  Vector3d(short _x, short _y, short _z) :
    Vertex(_x,_y,_z)
  {
  }

  Vector3d(Vertex v) :
    Vertex(v)
  {
  }

  Vector3d CrossProduct(const Vector3d& v) const;
  Vector3d Normalize() const;
};

#pragma once
#include "vertex.hpp"
//#include <vector>

class Vector3d : public Vertex
{

public:

  Vector3d(int _x, int _y, int _z) :
    Vertex(_x,_y,_z)
  {
  }

  Vector3d(Vertex v) :
    Vertex(v)
  {
  }
  void Normalize();
};

//using Vectors = std::vector<Vector3d>;

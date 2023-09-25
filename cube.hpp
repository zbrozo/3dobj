#pragma once

#include "object3d.hpp"

class Cube : public Object3D
{

public:

  Cube() :
    Object3D("cube")
  {
  }

  void Generate();

private:

  Vertices CreateVertices(int step, int degX, int degY);
  void CreateFaceWithVertices(const Vertices& tmpVertices,
                             Face& oFace,
                             Vertices& oVertices);


};

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

  void CreateFaceWithVertices(int step, int degX, int degY, Face& face, Vertices& vertices);
  void ProcessFaceWithVertices(Face& face, Vertices& vertices);

};

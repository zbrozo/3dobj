#pragma once

#include "object3d.hpp"

class Cube : public Object3D
{

public:

  Cube(const char* name) :
    Object3D(name)
  {
  }

  void Generate();
};

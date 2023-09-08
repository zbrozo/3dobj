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

};

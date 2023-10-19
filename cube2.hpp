#pragma once

#include "cube.hpp"

class Cube2 : public Cube
{

public:

  Cube2(const char* name) :
    Cube(name)
  {
  }
  
  void Generate();

protected:

  auto CreateCubePart1();
  auto CreateCubePart2();
  
};

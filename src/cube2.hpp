#pragma once

#include "cube.hpp"

class Cube2 : public Cube
{

public:

  Cube2(const char* name) :
    Cube(name)
  {
  }

  virtual ~Cube2() = default;
  
  Cube2(Cube2 const &) = delete;
  Cube2(Cube2 &&) = delete;
  Cube2& operator=(const Cube2& v) = delete;
  Cube2& operator=(Cube2 &&) = delete;
  
  void Generate();

protected:

  auto CreateCubePart1();
  auto CreateCubePart2();
  
};

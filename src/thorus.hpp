#pragma once

#include "object3d.hpp"

class Thorus : public Object3D
{

  int mCircleSize;
  int mRingSize;
  
public:

  Thorus(int circleSize, int ringSize, const char* name) :
    Object3D(name),
    mCircleSize(circleSize), mRingSize(ringSize)
  {
  }
  
  Thorus(int circleSize, int ringSize) :
    Object3D("thorus"),
    mCircleSize(circleSize), mRingSize(ringSize)
  {
  }

  virtual ~Thorus() = default;
  
  Thorus(Thorus const &) = delete;
  Thorus(Thorus &&) = delete;
  Thorus& operator=(const Thorus& v) = delete;
  Thorus& operator=(Thorus &&) = delete;
  
  void Generate();
};

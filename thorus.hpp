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

  void Generate();

private:

};

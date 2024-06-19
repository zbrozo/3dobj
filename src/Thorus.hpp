#pragma once

#include "Object3d.hpp"
#include "IGenerator.hpp"
#include <optional>

class Thorus : public Object3D, public IGenerator
{
  int mCircleAmount = 10;
  int mRingAmount = 10;
  int mCircleRadius = 30;
  int mCircleOffset = 50;
  
public:

  Thorus(
    const char* name,
    std::optional<int> circleAmount,
    std::optional<int> ringAmount,
    std::optional<int> circleRadius,
    std::optional<int> circleOffset);

  virtual ~Thorus() = default;
  
  Thorus(Thorus const &) = delete;
  Thorus(Thorus &&) = delete;
  Thorus& operator=(const Thorus& v) = delete;
  Thorus& operator=(Thorus &&) = delete;
  
  virtual void Generate() override;
};

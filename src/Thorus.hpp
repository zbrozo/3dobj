#pragma once

#include "Object3D.hpp"
#include "IGenerator.hpp"
#include <optional>

class Thorus : public Object3D, public IGenerator
{
  int mCircleAmount = 10;
  int mRingAmount = 10;
  int mCircleRadius = 30;
  int mCircleOffset = 50;
  int mCircleSinusStepX = 0;
  int mCircleSinusAmpX = 0;
  int mCircleSinusStepY = 0;
  int mCircleSinusAmpY = 0;
  int mCircleSinusStepZ = 0;
  int mCircleSinusAmpZ = 0;
  
public:

  Thorus(
    const char* name,
    std::optional<int> circleAmount,
    std::optional<int> ringAmount,
    std::optional<int> circleRadius,
    std::optional<int> circleOffset,
    std::optional<int> circleSinusStepX,
    std::optional<int> circleSinusAmpX,
    std::optional<int> circleSinusStepY,
    std::optional<int> circleSinusAmpY,
    std::optional<int> circleSinusStepZ,
    std::optional<int> circleSinusAmpZ
    );

  virtual ~Thorus() = default;
  
  Thorus(Thorus const &) = delete;
  Thorus(Thorus &&) = delete;
  Thorus& operator=(const Thorus& v) = delete;
  Thorus& operator=(Thorus &&) = delete;
  
  virtual void Generate() override;

private:

  Vertices CreateCircleVertices();
  Vertices CreateRingVertices(Vertices circle);
  Vertices MakeSinus(const Vertices& vertices, int step);
  

};

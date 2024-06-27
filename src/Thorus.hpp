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
  int mRingSinusStepX = 0;
  int mRingSinusAmpX = 0;
  int mRingSinusStepY = 0;
  int mRingSinusAmpY = 0;
  int mRingSinusStepZ = 0;
  int mRingSinusAmpZ = 0;
  
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
    std::optional<int> circleSinusAmpZ,
    std::optional<int> ringSinusStepX,
    std::optional<int> ringSinusAmpX,
    std::optional<int> ringSinusStepY,
    std::optional<int> ringSinusAmpY,
    std::optional<int> ringSinusStepZ,
    std::optional<int> ringSinusAmpZ    
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
  
  Vertices ApplySinusToRing(const Vertices& vertices);
  Vertices ApplySinusToCircle(const Vertices& vertices, int step);

};

#pragma once

#include "CubeExt.hpp"
#include "IGenerator.hpp"
#include "Object3D.hpp"
#include "Params.hpp"

#include <memory>
#include <vector>

class ComponetsVector;

class Cuboid : public Object3D, public IGenerator
{

  std::unique_ptr<ComponentsWithParamsVector> mObjects = nullptr;
  
public:
  Cuboid(const char *name, std::unique_ptr<ComponentsWithParamsVector> objects) :
    Object3D(name), mObjects(std::move(objects))
  {
  }
  
  virtual ~Cuboid() = default;
  
  Cuboid(Cuboid const &) = delete;
  Cuboid(Cuboid &&) = delete;
  Cuboid& operator=(const Cuboid&) = delete;
  Cuboid& operator=(Cuboid &&) = delete;
  
  virtual void Generate() override;
};

#pragma once

#include "CubeExt.hpp"
#include "IGenerator.hpp"
#include "Object3D.hpp"
#include "Params.hpp"

#include <memory>
#include <vector>

class ComponetsVector;

class Composite : public Object3D, public IGenerator
{

  std::unique_ptr<ComponentsWithParamsVector> mObjects = nullptr;
  
public:
  Composite(const char *name, std::unique_ptr<ComponentsWithParamsVector> objects) :
    Object3D(name), mObjects(std::move(objects))
  {
  }
  
  virtual ~Composite() = default;
  
  Composite(Composite const &) = delete;
  Composite(Composite &&) = delete;
  Composite& operator=(const Composite&) = delete;
  Composite& operator=(Composite &&) = delete;
  
  virtual void Generate() override;
};

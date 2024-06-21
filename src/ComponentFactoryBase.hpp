#pragma once

#include <memory>
#include "Params.hpp"

class Object3D;

class ComponentFactoryBase
{
public:

  std::unique_ptr<Object3D> Create(
    const std::string& name,
    const ParamsVector& params) const;

protected:
  
  virtual std::unique_ptr<Object3D> FactoryMethod(
    const std::string& name,
    const ParamsVector& params) const = 0;

  void Generate(Object3D& object) const;
};

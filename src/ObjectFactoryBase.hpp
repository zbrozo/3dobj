#pragma once

#include "Params.hpp"

#include <vector>
#include <string>
#include <memory>
#include <functional>

class Object3D;
using ComponentFactories = std::vector<std::function<std::unique_ptr<Object3D>(const ParamsMap&)>>;

class ObjectFactoryBase
{
  ComponentFactories mAllComponentFactories;
  
public:

  ObjectFactoryBase();
  
  std::unique_ptr<Object3D> Create(
    const std::string& name,
    const ParamsMap& params) const;

  const ComponentFactories& GetAllComponentFactories() const
  {
    return mAllComponentFactories;
  }
  
protected:
  
  virtual std::unique_ptr<Object3D> FactoryMethod(
    const std::string& name,
    const ParamsMap& params) const = 0;

  void Generate(Object3D& object) const;

  std::string CreateFullName(
    const std::string& name,
    const ParamsMap& params) const;
};

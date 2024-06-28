#pragma once

#include <memory>
#include "Params.hpp"

class Object3D;

class ComponentFactoryBase
{
public:

  ComponentFactoryBase() = default;
  virtual ~ComponentFactoryBase() = default;

  ComponentFactoryBase(const ComponentFactoryBase&) = delete;
  ComponentFactoryBase(ComponentFactoryBase&&) = delete;
  ComponentFactoryBase& operator=(const ComponentFactoryBase&) = delete;
  ComponentFactoryBase& operator=(ComponentFactoryBase&&) = delete;
  
  std::unique_ptr<Object3D> Create(
    const std::string& name,
    const ParamsVector& params) const;

protected:
  
  virtual std::unique_ptr<Object3D> FactoryMethod(
    const std::string& name,
    const ParamsVector& params) const = 0;

  void Generate(Object3D& object) const;
};

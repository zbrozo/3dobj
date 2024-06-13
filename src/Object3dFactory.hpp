#pragma once

#include "Params.hpp"

#include <vector>
#include <string>
#include <memory>

class Object3D;

using Object3dParams = std::vector<std::string>;

class ObjectFactory
{
public:
  
  std::unique_ptr<Object3D> Create(
    const std::string& name,
    const ParamsMap& params) const;
  
protected:
  
  virtual std::unique_ptr<Object3D> FactoryMethod(
    const std::string& name,
    const ParamsMap& params) const = 0;

  void Generate(Object3D& object) const;
};

class CubeFactory : public ObjectFactory
{
public:
  std::unique_ptr<Object3D> FactoryMethod(
    const std::string& name,
    const ParamsMap& params) const override;
};

class CubeExtFactory : public ObjectFactory
{
public:
  std::unique_ptr<Object3D> FactoryMethod(
    const std::string& name,
    const ParamsMap& params) const override;
};

class ThorusFactory : public ObjectFactory
{
public:
  std::unique_ptr<Object3D> FactoryMethod(
    const std::string& name,
    const ParamsMap& params) const override;
};

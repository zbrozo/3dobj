#pragma once
#include "Object3d.hpp"
#include "IGenerator.hpp"

#include <vector>
#include <string>
#include <memory>

using Params = std::vector<std::string>;

class IObjectFactory
{
public:
  virtual std::unique_ptr<Object3D> Create(
    const std::string& name,
    const Params& params) = 0;
};

class ObjectFactory : public IObjectFactory
{
public:

  // factory method
  void Generate(Object3D& object);
};

class CubeFactory : public ObjectFactory
{
public:
  std::unique_ptr<Object3D> Create(const std::string& name, const Params& params) override;
};

class Cube2Factory : public ObjectFactory
{
public:
  std::unique_ptr<Object3D> Create(const std::string& name, const Params& params) override;
};

class ThorusFactory : public ObjectFactory
{
public:
  std::unique_ptr<Object3D> Create(const std::string& name, const Params& params) override;
};

#pragma once

#include <vector>
#include <string>
#include <memory>

class Object3D;

using Params = std::vector<std::string>;
/*
class IObjectFactory
{
public:

  virtual std::unique_ptr<Object3D> Create(const std::string& name, const Params& params) = 0;
  
protected:
  
  virtual std::unique_ptr<Object3D> FactoryMethod(
    const std::string& name,
    const Params& params) = 0;
};
*/
class ObjectFactory //: public IObjectFactory
{
public:
  
  std::unique_ptr<Object3D> Create(const std::string& name, const Params& params);
  
protected:
  
  virtual std::unique_ptr<Object3D> FactoryMethod(
    const std::string& name,
    const Params& params) = 0;

  void Generate(Object3D& object);
};

class CubeFactory : public ObjectFactory
{
public:
  std::unique_ptr<Object3D> FactoryMethod(const std::string& name, const Params& params) override;
};

class Cube2Factory : public ObjectFactory
{
public:
  std::unique_ptr<Object3D> FactoryMethod(const std::string& name, const Params& params) override;
};

class ThorusFactory : public ObjectFactory
{
public:
  std::unique_ptr<Object3D> FactoryMethod(const std::string& name, const Params& params) override;
};

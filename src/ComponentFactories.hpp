#include "ComponentFactoryBase.hpp"

class Object3D;

class Component0Factory : public ComponentFactoryBase
{
public:
  std::unique_ptr<Object3D> FactoryMethod(
    const std::string& name,
    const ParamsMap& params) const override;
};

class Component1Factory : public ComponentFactoryBase
{
public:
  std::unique_ptr<Object3D> FactoryMethod(
    const std::string& name,
    const ParamsMap& params) const override;
};

class Component2Factory : public ComponentFactoryBase
{
public:
  std::unique_ptr<Object3D> FactoryMethod(
    const std::string& name,
    const ParamsMap& params) const override;
};

class Component3Factory : public ComponentFactoryBase
{
public:
  std::unique_ptr<Object3D> FactoryMethod(
    const std::string& name,
    const ParamsMap& params) const override;
};

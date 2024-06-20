#include "ComponentFactoryBase.hpp"
#include "IGenerator.hpp"
#include "Object3D.hpp"

std::unique_ptr<Object3D> ComponentFactoryBase::Create(
  const std::string& name,
  const ParamsMap& params) const
{
  auto object = FactoryMethod(name, params);
  Generate(*object);
  return object;
}

void ComponentFactoryBase::Generate(Object3D& object) const
{
  auto& generator = dynamic_cast<IGenerator&>(object);
  generator.Generate();
}

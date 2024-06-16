#include "Object3dFactory.hpp"
#include "Cube.hpp"
#include "CubeExt.hpp"
#include "ObjectComponents.hpp"
#include "Thorus.hpp"
#include "Params.hpp"

#include <memory>
#include <stdexcept>
#include <iostream>

namespace
{
  const std::string TooLessParamsMessage = "Too less parameters for ";

  ComponentsVector allComponentsVector;

  void InitAllComponentsVector()
  {
    allComponentsVector.push_back(std::make_unique<Component0>());
    allComponentsVector.push_back(std::make_unique<Component1>());
    allComponentsVector.push_back(std::make_unique<Component2>());
  }
}

std::unique_ptr<Object3D> ObjectFactory::Create(
  const std::string& name,
  const ParamsMap& params) const
{
  InitAllComponentsVector();
  
  auto object = FactoryMethod(name, params);
  Generate(*object);
  return object;
}

void ObjectFactory::Generate(Object3D& object) const
{
  auto& generator = dynamic_cast<IGenerator&>(object);
  generator.Generate();
  
  object.CreateNormalVectors();
}

std::unique_ptr<Object3D> CubeFactory::FactoryMethod(
  const std::string& name,
  const ParamsMap& /*params*/) const
{
  auto object = std::make_unique<Cube>(name.c_str());
  return object;
}

std::unique_ptr<Object3D> CubeExtFactory::FactoryMethod(
  const std::string& name,
  const ParamsMap& params) const 
{
  auto components = std::make_unique<ComponentsVector>();
  
  for (int i : params.at(ParamsId::ComponentsList))
  {
    components->push_back(std::move(allComponentsVector[i]));
  }
  
  auto object = std::make_unique<CubeExt>(name.c_str(), std::move(components));
  return object;
}

std::unique_ptr<Object3D> ThorusFactory::FactoryMethod(
  const std::string& name,
  const ParamsMap& params) const
{
  const auto& additionalParams = params.at(ParamsId::AdditionalParams);
  
  if (additionalParams.size() < 2)
  {
    throw std::out_of_range(TooLessParamsMessage + name);
  }
  
  const auto circleSize = additionalParams[0];
  const auto ringSize = additionalParams[1];
  const auto nameExt = std::string(name) + "_" + std::to_string(circleSize) + "_" + std::to_string(ringSize);
  
  auto object = std::make_unique<Thorus>(
    circleSize,
    ringSize,
    nameExt.c_str());

  return object;
}

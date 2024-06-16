#include "Object3dFactory.hpp"
#include "Cube.hpp"
#include "CubeExt.hpp"
#include "ObjectComponents.hpp"
#include "Thorus.hpp"
#include "Params.hpp"

#include <memory>
#include <stdexcept>
#include <iostream>
#include <algorithm>

using namespace std::placeholders;

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

std::string ObjectFactory::CreateName(const std::string& name, const ParamsMap &params) const
{
  std::string result = name;

  auto appendParams = [&](const ParamsMap::const_iterator& it) {
    for (int value : it->second)
    {
      result += "_" + std::to_string(value);
    }
  };

  auto findParamVector = [](const std::pair<ParamsId, ParamsVector>& x, ParamsId id) {
    return x.first == id;
  };
  
  if (auto it = std::find_if(params.begin(), params.end(),
      std::bind(findParamVector, _1,  ParamsId::ComponentsList)); it != params.end())
  {
    appendParams(it);
  }

  if (auto it = std::find_if(params.begin(), params.end(),
      std::bind(findParamVector, _1,  ParamsId::ComponentsParams)); it != params.end())
  {
    appendParams(it);
  }

  if (auto it = std::find_if(params.begin(), params.end(),
      std::bind(findParamVector, _1,  ParamsId::AdditionalParams)); it != params.end())
  {
    appendParams(it);
  }
  
  return result;
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
  return std::make_unique<Cube>(name.c_str());
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

  const auto nameExt = CreateName(name, params);
  
  return std::make_unique<CubeExt>(nameExt.c_str(), std::move(components));
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
  const auto nameExt = CreateName(name, params);
  
  return std::make_unique<Thorus>(
    circleSize,
    ringSize,
    nameExt.c_str());
}

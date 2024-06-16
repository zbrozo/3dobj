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
#include <optional>

using namespace std::placeholders;

using ComponentFactories = std::vector<std::function<std::unique_ptr<Object3D>(const ParamsMap&)>>;
  
namespace
{
  const std::string TooLessParamsMessage = "Too less parameters for ";

  ComponentFactories allComponentFactories;

  auto findParamsVector = [](const std::pair<ParamsId, ParamsVector>& params, ParamsId id) {
    return params.first == id;
  };
  
  void InitAllComponentFactoriesVector()
  {
    allComponentFactories.push_back([](const ParamsMap& params){
      std::optional<int> param;
      
      if (auto it = std::find_if(params.begin(), params.end(),
          std::bind(findParamsVector, _1,  ParamsId::ComponentsParams)); it != params.end())
      {
        param = it->second[0];
      }
      
      return std::make_unique<Component0>(param);
    });

    allComponentFactories.push_back([](const ParamsMap& params){
      std::optional<int> param1;
      std::optional<int> param2;
      std::optional<int> param3;
      
      if (auto it = std::find_if(params.begin(), params.end(),
          std::bind(findParamsVector, _1,  ParamsId::ComponentsParams)); it != params.end())
      {
        
        param1 = it->second[0];
        param2 = it->second[1];
        param3 = it->second[2];


        std::cout << "aaaaaa" << param1.value();

      }
      
      return std::make_unique<Component1>(param1, param2, param3);
    });

    allComponentFactories.push_back([](const ParamsMap& params){
      std::optional<int> param1;
      std::optional<int> param2;
      
      if (auto it = std::find_if(params.begin(), params.end(),
          std::bind(findParamsVector, _1,  ParamsId::ComponentsParams)); it != params.end())
      {
        param1 = it->second[0];
        param2 = it->second[1];
      }
      
      return std::make_unique<Component2>(param1, param2);
    });
  }

}

std::unique_ptr<Object3D> ObjectFactory::Create(
  const std::string& name,
  const ParamsMap& params) const
{
  InitAllComponentFactoriesVector();
  
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
  
  if (auto it = std::find_if(params.begin(), params.end(),
      std::bind(findParamsVector, _1,  ParamsId::ComponentsList)); it != params.end())
  {
    appendParams(it);
  }

  if (auto it = std::find_if(params.begin(), params.end(),
      std::bind(findParamsVector, _1,  ParamsId::ComponentsParams)); it != params.end())
  {
    appendParams(it);
  }

  if (auto it = std::find_if(params.begin(), params.end(),
      std::bind(findParamsVector, _1,  ParamsId::AdditionalParams)); it != params.end())
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
  const ParamsMap& params) const
{
  if (auto it = std::find_if(params.begin(), params.end(),
      std::bind(findParamsVector, _1,  ParamsId::AdditionalParams)); it != params.end())
  {
    return std::make_unique<Cube>(name.c_str(), it->second[0]);
  }
  
  return std::make_unique<Cube>(name.c_str());
}

std::unique_ptr<Object3D> CubeExtFactory::FactoryMethod(
  const std::string& name,
  const ParamsMap& params) const 
{
  auto components = std::make_unique<ComponentsVector>();

  for (int i : params.at(ParamsId::ComponentsList))
  {
    components->push_back(std::move(allComponentFactories[i](params)));
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

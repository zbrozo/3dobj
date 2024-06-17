#include "ObjectFactoryBase.hpp"
#include "IGenerator.hpp"
#include "ObjectComponents.hpp"

#include <algorithm>
#include <optional>

using namespace std::placeholders;

namespace
{
  auto findParamsVector = [](const std::pair<ParamsId, ParamsVector>& params, ParamsId id) {
    return params.first == id;
  };
  
  void InitAllComponentFactoriesVector(ComponentFactories& allComponentFactories)
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
          std::bind(findParamsVector, _1, ParamsId::ComponentsParams)); it != params.end())
      {
        param1 = it->second[0];
        param2 = it->second[1];
        param3 = it->second[2];
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

ObjectFactoryBase::ObjectFactoryBase()
{
  InitAllComponentFactoriesVector(mAllComponentFactories);
}

std::unique_ptr<Object3D> ObjectFactoryBase::Create(
  const std::string& name,
  const ParamsMap& params) const
{
  auto object = FactoryMethod(name, params);
  Generate(*object);
  return object;
}

std::string ObjectFactoryBase::CreateName(const std::string& name, const ParamsMap &params) const
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

void ObjectFactoryBase::Generate(Object3D& object) const
{
  auto& generator = dynamic_cast<IGenerator&>(object);
  generator.Generate();
  
  object.CreateNormalVectors();
}

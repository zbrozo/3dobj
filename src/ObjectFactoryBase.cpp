#include "ObjectFactoryBase.hpp"
#include "IGenerator.hpp"
#include "Components.hpp"
#include "ComponentFactories.hpp"
#include "Params.hpp"

#include <algorithm>
#include <optional>

using namespace std::placeholders;

namespace
{

auto findParamsVector = [](const ParamsPair& params, ParamsId id) {
  return params.first == id;
};

void InitAllComponentFactoriesVector(ComponentFactories& allComponentFactories)
{
  allComponentFactories[ObjectId::Square] = std::make_unique<Components::SquareFactory>();
  allComponentFactories[ObjectId::Rectangle] = std::make_unique<Components::RectangleFactory>();
  allComponentFactories[ObjectId::SquareHolePart1] = std::make_unique<Components::SquareWithHolePart1Factory>();
  allComponentFactories[ObjectId::SquareHolePart2] = std::make_unique<Components::SquareWithHolePart2Factory>();
  allComponentFactories[ObjectId::Pyramid] = std::make_unique<Components::PyramidFactory>();
}

} // namespace

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

std::string ObjectFactoryBase::CreateFullName(const std::string& name, const ParamsMap &params) const
{
  std::string result = name;
  
  auto appendNames = [&](const ParamsMap::const_iterator& it)
  {
    for (std::string value : std::get<ComponentNamesVector>(it->second))
    {
      result += "_" + value;
    }
  };
  
  auto appendParams = [&](const ParamsMap::const_iterator& it)
  {
    for (int value : std::get<ParamsVector>(it->second))
    {
      result += "_" + std::to_string(value);
    }
  };
  
  if (auto it = std::find_if(params.begin(), params.end(),
      std::bind(findParamsVector, _1,  ParamsId::ComponentsList)); it != params.end())
  {
    appendNames(it);
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

#include "ComponentFactories.hpp"
#include "Components.hpp"
#include "Object3D.hpp"
#include "Params.hpp"

#include <memory>
#include <optional>
#include <algorithm>

using namespace std::placeholders;

namespace
{

auto findParamsVector = [](const std::pair<ParamsId, ParamsVector> &params, ParamsId id)
{
  return params.first == id;
};

auto getParam(std::vector<int> values, unsigned int index)
{
  if (values.size() > index)
  {
    return std::optional<int>{values[index]};
  }
    
  return std::optional<int>();
}
  
} // namespace
  
std::unique_ptr<Object3D> Component0Factory::FactoryMethod(
  const std::string& /*name*/,
  const ParamsMap& params) const
{
  std::optional<int> param;
  
  if (auto it = std::find_if(params.begin(), params.end(),
      std::bind(findParamsVector, _1,  ParamsId::ComponentsParams)); it != params.end())
  {
    param = getParam(it->second, 0);
  }
  
  return std::make_unique<Components::Square>(param);
}

std::unique_ptr<Object3D> Component1Factory::FactoryMethod(
  const std::string& /*name*/,
  const ParamsMap& params) const
{
  std::optional<int> param1;
  std::optional<int> param2;
  std::optional<int> param3;
  
  if (auto it = std::find_if(params.begin(), params.end(),
      std::bind(findParamsVector, _1, ParamsId::ComponentsParams)); it != params.end())
  {
    param1 = getParam(it->second, 0);
    param2 = getParam(it->second, 1);
    param3 = getParam(it->second, 2);
  }

  return std::make_unique<Components::SquareWithHolePart1>(param1, param2, param3);
}

std::unique_ptr<Object3D> Component2Factory::FactoryMethod(
  const std::string& /*name*/,
  const ParamsMap& params) const
{
  std::optional<int> param1;
  std::optional<int> param2;
      
  if (auto it = std::find_if(params.begin(), params.end(),
      std::bind(findParamsVector, _1,  ParamsId::ComponentsParams)); it != params.end())
  {
    param1 = getParam(it->second, 0);
    param2 = getParam(it->second, 1);
  }
  
  return std::make_unique<Components::SquareWithHolePart2>(param1, param2);
}

std::unique_ptr<Object3D> Component3Factory::FactoryMethod(
  const std::string& /*name*/,
  const ParamsMap& params) const
{
  std::optional<int> param1;
  std::optional<int> param2;
      
  if (auto it = std::find_if(params.begin(), params.end(),
      std::bind(findParamsVector, _1,  ParamsId::ComponentsParams)); it != params.end())
  {
    param1 = getParam(it->second, 0);
    param2 = getParam(it->second, 1);
  }
  
  return std::make_unique<Components::Pyramid>(param1, param2);
}

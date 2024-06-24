#include "ComponentFactories.hpp"
#include "Components.hpp"
#include "Object3D.hpp"
#include "Params.hpp"

#include <memory>
#include <optional>
#include <algorithm>

#include <boost/log/trivial.hpp>

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

namespace Components
{

std::unique_ptr<Object3D> SquareFactory::FactoryMethod(
  const std::string& /*name*/,
  const ParamsVector& params) const
{
  std::optional<int> param = getParam(params, 0);
  return std::make_unique<Components::Square>(param);
}

std::unique_ptr<Object3D> SquareWithHolePart1Factory::FactoryMethod(
  const std::string& /*name*/,
  const ParamsVector& params) const
{
  
  std::optional<int> param1 = getParam(params, 0);
  std::optional<int> param2 = getParam(params, 1);
  std::optional<int> param3 = getParam(params, 2);
  return std::make_unique<Components::SquareWithHolePart1>(param1, param2, param3);
}

std::unique_ptr<Object3D> SquareWithHolePart2Factory::FactoryMethod(
  const std::string& /*name*/,
  const ParamsVector& params) const
{
  std::optional<int> param1 = getParam(params, 0);
  std::optional<int> param2 = getParam(params, 1);
  return std::make_unique<Components::SquareWithHolePart2>(param1, param2);
}

std::unique_ptr<Object3D> PyramidFactory::FactoryMethod(
  const std::string& /*name*/,
  const ParamsVector& params) const
{
  std::optional<int> param1 = getParam(params, 0);
  std::optional<int> param2 = getParam(params, 1);
  return std::make_unique<Components::Pyramid>(param1, param2);
}

} // namespace Components

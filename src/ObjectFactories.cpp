#include "ObjectFactories.hpp"
#include "Cube.hpp"
#include "CubeExt.hpp"
#include "Thorus.hpp"
#include "ObjectComponents.hpp"
#include "Params.hpp"

#include <memory>
#include <stdexcept>
#include <algorithm>

using namespace std::placeholders;

namespace
{
  const std::string TooLessParamsMessage = "Too less parameters for ";

  auto findParamsVector = [](const std::pair<ParamsId, ParamsVector>& params, ParamsId id) {
    return params.first == id;
  };
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
    components->push_back(std::move(GetAllComponentFactories()[i](params)));
  }

  const auto nameExt = CreateFullName(name, params);
  
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
  const auto nameExt = CreateFullName(name, params);
  
  return std::make_unique<Thorus>(
    circleSize,
    ringSize,
    nameExt.c_str());
}

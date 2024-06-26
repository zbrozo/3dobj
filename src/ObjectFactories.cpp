#include "ObjectFactories.hpp"
#include "Cube.hpp"
#include "CubeExt.hpp"
#include "Thorus.hpp"
#include "Cuboid.hpp"
#include "Components.hpp"
#include "Params.hpp"

#include <cctype>
#include <memory>
#include <stdexcept>
#include <algorithm>

#include <boost/log/trivial.hpp>
#include <boost/algorithm/string.hpp>

using namespace std::placeholders;

namespace
{

std::map<std::string, ObjectId> ComponentIdMap {
  {"square", ObjectId::Square},
  {"rectangle", ObjectId::Rectangle},
  {"squareholepart1", ObjectId::SquareHolePart1},
  {"squareholepart2", ObjectId::SquareHolePart2},
  {"pyramid", ObjectId::Pyramid},
  {"taper", ObjectId::Taper},
};  

const std::string TooLessParamsMessage = "Too less parameters for ";

auto findParamsVector = [](const ParamsPair& params,  ParamsId id)
{
  return params.first == id;
};

auto getParam(ParamsVector values, unsigned int index)
{
  if (values.size() > index)
  {
    return std::optional<int>{values[index]};
  }
  
  return std::optional<int>();
}

}

std::unique_ptr<Object3D> CubeFactory::FactoryMethod(
  const std::string& name,
  const ParamsMap& params) const
{
  if (auto it = std::find_if(params.begin(), params.end(),
      std::bind(findParamsVector, _1,  ParamsId::AdditionalParams)); it != params.end())
  {
    return std::make_unique<Cube>(name.c_str(), std::get<ParamsVector>(it->second)[0]);
  }
  
  return std::make_unique<Cube>(name.c_str());
}

std::unique_ptr<Object3D> CubeExtFactory::FactoryMethod(
  const std::string& name,
  const ParamsMap& params) const 
{
  auto components = std::make_unique<ComponentsVector>();
  auto componentsWithParamsVector = std::make_unique<ComponentsWithParamsVector>();
  
  const auto& names =  std::get<ComponentNamesVector>(params.at(ParamsId::ComponentsList));

  ParamsVector paramsVector;
  ParamsVector componentParamsVector;
    
  if (auto it = std::find_if(params.begin(), params.end(),
      std::bind(findParamsVector, _1,  ParamsId::ComponentsParams)); it != params.end())
  {
    componentParamsVector = std::get<ParamsVector>(it->second);
  }

  if (auto it = std::find_if(params.begin(), params.end(),
      std::bind(findParamsVector, _1,  ParamsId::Params)); it != params.end())
  {
    paramsVector = std::get<ParamsVector>(it->second);
  }
    
  for (auto name : names)
  {
    boost::algorithm::to_lower(name);
    const auto id = ComponentIdMap[name];
    BOOST_LOG_TRIVIAL(trace) << "Found component: " << name << " " << std::to_string(static_cast<int>(id));
    components->push_back(std::move(GetAllComponentFactories().at(id)->Create(name, componentParamsVector)));
  }

  componentsWithParamsVector->push_back(
    ComponentsWithParamsPair(paramsVector, std::move(components)));
  
  const auto nameExt = CreateFullName(name, params);
  return std::make_unique<CubeExt>(nameExt.c_str(), std::move(componentsWithParamsVector));
}

std::unique_ptr<Object3D> ThorusFactory::FactoryMethod(
  const std::string& name,
  const ParamsMap& params) const
{
  const auto& foundParams = std::get<ParamsVector>(params.at(ParamsId::AdditionalParams));
  
  const auto circleAmount = getParam(foundParams, 0);
  const auto ringAmount = getParam(foundParams, 1);
  const auto circleRadius = getParam(foundParams, 2);
  const auto circleOffset = getParam(foundParams, 3);
  
  const auto nameExt = CreateFullName(name, params);
  
  return std::make_unique<Thorus>(nameExt.c_str(),
    circleAmount, ringAmount, circleRadius, circleOffset);
}

std::unique_ptr<Object3D> CuboidFactory::FactoryMethod(
  const std::string& name,
  const ParamsMap& params) const 
{
  auto componentsWithParamsVector = std::make_unique<ComponentsWithParamsVector>();

  auto create = [&params, &componentsWithParamsVector, &name, this]
    (ParamsId listId, ParamsId paramsId, ParamsId mainParamsId)
  {
    auto components = std::make_unique<ComponentsVector>();

    ParamsVector paramsVector;
    ParamsVector mainParamsVector;
    
    if (auto it = std::find_if(params.begin(), params.end(),
        std::bind(findParamsVector, _1,  paramsId)); it != params.end())
    {
      paramsVector = std::get<ParamsVector>(it->second);
    }
    
    if (auto it = std::find_if(params.begin(), params.end(),
        std::bind(findParamsVector, _1,  mainParamsId)); it != params.end())
    {
      mainParamsVector = std::get<ParamsVector>(it->second);
    }
    
    if (auto it = std::find_if(params.begin(), params.end(),
        std::bind(findParamsVector, _1,  listId)); it != params.end())
    {
      const auto& names = std::get<ComponentNamesVector>(it->second);
        
      for (auto name : names)
      {
        boost::algorithm::to_lower(name);
        const auto id = ComponentIdMap[name];
        BOOST_LOG_TRIVIAL(trace) << "Found component: " << name << " " << std::to_string(static_cast<int>(id));

        components->push_back(
          std::move(GetAllComponentFactories().at(id)->Create(name, paramsVector)));
      }
    }

    componentsWithParamsVector->push_back(
      ComponentsWithParamsPair(mainParamsVector, std::move(components)));
  };
  
  create(ParamsId::ComponentsList0, ParamsId::ComponentsParams0, ParamsId::Params0);
  create(ParamsId::ComponentsList1, ParamsId::ComponentsParams1, ParamsId::Params1);
  create(ParamsId::ComponentsList2, ParamsId::ComponentsParams2, ParamsId::Params2);
  create(ParamsId::ComponentsList3, ParamsId::ComponentsParams3, ParamsId::Params3);
  create(ParamsId::ComponentsList4, ParamsId::ComponentsParams4, ParamsId::Params4);
  create(ParamsId::ComponentsList5, ParamsId::ComponentsParams5, ParamsId::Params5);
    
  const auto nameExt = CreateFullName(name, params);
  
  return std::make_unique<Cuboid>(nameExt.c_str(), std::move(componentsWithParamsVector));
}

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
  {"squareholepart1", ObjectId::SquareHolePart1},
  {"squareholepart2", ObjectId::SquareHolePart2},
  {"pyramid", ObjectId::Pyramid},
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

  const auto& names =  std::get<ComponentNamesVector>(params.at(ParamsId::ComponentsList));
  
  for (auto name : names)
  {
    boost::algorithm::to_lower(name);

    const auto id = ComponentIdMap[name];
           
    ParamsVector paramsVector;
    
    if (auto it = std::find_if(params.begin(), params.end(),
        std::bind(findParamsVector, _1,  ParamsId::ComponentsParams)); it != params.end())
    {
      paramsVector = std::get<ParamsVector>(it->second);
    }
    
    components->push_back(std::move(GetAllComponentFactories().at(id)->Create(name, paramsVector)));
  }

  const auto nameExt = CreateFullName(name, params);
  
  return std::make_unique<CubeExt>(nameExt.c_str(), std::move(components));
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
  auto componentsPerFaceVector = std::make_unique<ComponentsPerFaceVector>();

  auto create = [&params, &componentsPerFaceVector, &name, this]
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

    componentsPerFaceVector->push_back(
      ComponentsAndMainParamsPair(mainParamsVector, std::move(components)));
  };
  
  create(ParamsId::ComponentsListFace0, ParamsId::ComponentsParamsFace0, ParamsId::ParamsFace0);
  create(ParamsId::ComponentsListFace1, ParamsId::ComponentsParamsFace1, ParamsId::ParamsFace1);
  create(ParamsId::ComponentsListFace2, ParamsId::ComponentsParamsFace2, ParamsId::ParamsFace2);
  create(ParamsId::ComponentsListFace3, ParamsId::ComponentsParamsFace3, ParamsId::ParamsFace3);
  create(ParamsId::ComponentsListFace4, ParamsId::ComponentsParamsFace4, ParamsId::ParamsFace4);
  create(ParamsId::ComponentsListFace5, ParamsId::ComponentsParamsFace5, ParamsId::ParamsFace5);
    
  const auto nameExt = CreateFullName(name, params);
  
  return std::make_unique<Cuboid>(nameExt.c_str(), std::move(componentsPerFaceVector));
}

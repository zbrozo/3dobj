#include "IGenerator.hpp"
#include "Face.hpp"
#include "Object3d.hpp"
#include "Vector3d.hpp"
#include "Cube.hpp"
#include "CubeExt.hpp"
#include "Thorus.hpp"
#include "AmigaFile.hpp"
#include "Object3dFactory.hpp"
#include "Params.hpp"

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <array>
#include <map>
#include <memory>
#include <utility>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

enum class ObjectId {
  None = 0,
  Cube = 1,
  CubeExt = 2,
  Thorus = 3,
};

std::map<std::string, ObjectId> ObjectIdMap {
  {"cube", ObjectId::Cube},
  {"cube-ext", ObjectId::CubeExt},
  {"thorus", ObjectId::Thorus}
};

std::map<ObjectId, std::string> ParamsHelp {
  {ObjectId::Cube, ""},
  {ObjectId::CubeExt, ""},
  {ObjectId::Thorus, "thorusCircleSize thorusRingSize"}
};

using ObjectFactoryPair = std::pair<ObjectId, std::unique_ptr<ObjectFactory>>;
std::map<ObjectId, std::unique_ptr<ObjectFactory>> ObjectFactoryMap;

void InitObjectFactoryMap()
{
  ObjectFactoryMap.insert(ObjectFactoryPair(ObjectId::Cube, std::make_unique<CubeFactory>()));
  ObjectFactoryMap.insert(ObjectFactoryPair(ObjectId::CubeExt, std::make_unique<CubeExtFactory>()));
  ObjectFactoryMap.insert(ObjectFactoryPair(ObjectId::Thorus, std::make_unique<ThorusFactory>()));
}

const auto& GetFactory(const std::string& name)
{
  InitObjectFactoryMap();

  const auto it = ObjectIdMap.find(name);
  if (it == ObjectIdMap.end())
  {
      throw std::out_of_range("3d object id not found");
  }
  
  const auto creatorIt = ObjectFactoryMap.find(it->second);
  if (creatorIt == ObjectFactoryMap.end())
  {
    throw std::out_of_range("3d object factory not found");
  }

  return creatorIt->second;
}

void PrintParamsHelp()
{
  std::cout << "Possible 3d objects to use:\n";
  std::for_each(ObjectIdMap.begin(), ObjectIdMap.end(),
    [](std::pair<std::string, ObjectId> item)
      {
        std::cout << "  name: " << item.first << ", params: " << ParamsHelp[item.second];
        std::cout << "\n";
      });
}

auto ReadGeneratorParams(int argc, char *argv[], const po::options_description& desc)
{
  po::variables_map vm;
  po::positional_options_description p;
  p.add("additional-params", -1);

  po::store(po::command_line_parser(argc, argv).
          options(desc).positional(p).run(), vm);
  po::notify(vm);

  return vm;
}

int main(int argc, char* argv[])
{
  po::options_description optionsDesc("generator [options] <type> [params]\n");
  optionsDesc.add_options()
    ("help,h", "produce help message")
    ("verbose,v", "produce verbose logs")
    ("type,t", po::value<std::string>(), "object3d type")
    ("component-list,c", po::value<ParamsVector>()->multitoken(), "component id list")
    ("component-params,p", po::value<ParamsVector>()->multitoken(), "component params")
    ("additional-params", po::value<ParamsVector>(), "additional params");
  
  const po::variables_map& options = ReadGeneratorParams(argc, argv, optionsDesc);

  if (options.count("help"))
  {
    std::cout << optionsDesc << "\n";
    PrintParamsHelp();
    return 1;
  }
  
  const auto verbose = options.count("verbose");

  std::string name;
  if (options.count("type"))
  {
    name = options["type"].as<std::string>();
  }
  else
  {
    std::cout << optionsDesc << "\n";
    PrintParamsHelp();
    return 1;
  }

  std::map<ParamsId, ParamsVector> paramsMap {
    {ParamsId::ComponentsList, ParamsVector()},
    {ParamsId::ComponentsParams, ParamsVector()},
    {ParamsId::AdditionalParams, ParamsVector()}
  };
  
  if (options.count("component-list"))
  {
    const auto& list = options["component-list"].as<ParamsVector>();
    paramsMap[ParamsId::ComponentsList] = list;
  }

  if (options.count("component-params"))
  {
    const auto& list = options["component-params"].as<ParamsVector>();
    paramsMap[ParamsId::ComponentsParams] = list;
  }
  
  if (options.count("additional-params"))
  {
    const auto& params = options["additional-params"].as<ParamsVector>();
    paramsMap[ParamsId::AdditionalParams] = params;
  }
  
  try {
    const auto& factory = GetFactory(name);
    const auto object3d = factory->Create(name, paramsMap);

    AmigaFile file;
    file.Save(*object3d);

    if (verbose)
    {
      object3d->LogVertices();
      object3d->LogFaces();
    }
    
  } catch (const std::out_of_range& ex) {
    std::cout << ex.what() << "\n";
    PrintParamsHelp();
    return 1;
  } catch (const std::bad_cast& ex) {
    std::cout << ex.what() << "\n";
    PrintParamsHelp();
    return 1;
  }
  
  return 0;
  
}

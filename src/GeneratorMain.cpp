#include "IGenerator.hpp"
#include "Face.hpp"
#include "Object3d.hpp"
#include "Vector3d.hpp"
#include "Cube.hpp"
#include "CubeExt.hpp"
#include "Thorus.hpp"
#include "AmigaFile.hpp"
#include "Object3dFactory.hpp"

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
  p.add("object3d-params", -1);

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
    ("name,n", po::value<std::string>(), "object3d name")
    ("object3d-params", po::value<std::vector<std::string>>(), "object3d-params");
  
  const po::variables_map& options = ReadGeneratorParams(argc, argv, optionsDesc);

  if (options.count("help"))
  {
    std::cout << optionsDesc << "\n";
    PrintParamsHelp();
    return 1;
  }
  
  const auto verbose = options.count("verbose");

  std::string name;
  if (options.count("name"))
  {
    name = options["name"].as<std::string>();
  }
  else
  {
    std::cout << optionsDesc << "\n";
    PrintParamsHelp();
    return 1;
  }
  
  Object3dParams object3dParams;
  if (options.count("object3d-params"))
  {
    object3dParams = options["object3d-params"].as<std::vector<std::string>>();
  }

  try {
    const auto& factory = GetFactory(name);
    const auto object3d = factory->Create(name, object3dParams);

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

#include "IGenerator.hpp"
#include "Face.hpp"
#include "Object3d.hpp"
#include "Vector3d.hpp"
#include "Cube.hpp"
#include "Cube2.hpp"
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

enum class ObjectId {
  None = 0,
  Cube = 1,
  Cube2 = 2,
  Thorus = 3
};

std::map<std::string, ObjectId> ObjectIdMap {
  {"cube", ObjectId::Cube},
  {"cube2", ObjectId::Cube2},
  {"thorus", ObjectId::Thorus}
};

std::map<ObjectId, std::string> ParamsHelp {
  {ObjectId::Cube, ""},
  {ObjectId::Cube2, ""},
  {ObjectId::Thorus, "thorusCircleSize thorusRingSize"}
};

using ObjectFactoryPair = std::pair<ObjectId, std::unique_ptr<ObjectFactory>>;
std::map<ObjectId, std::unique_ptr<ObjectFactory>> ObjectFactoryMap;

void InitObjectFactoryMap()
{
  ObjectFactoryMap.insert(ObjectFactoryPair(ObjectId::Cube, std::make_unique<CubeFactory>()));
  ObjectFactoryMap.insert(ObjectFactoryPair(ObjectId::Cube2, std::make_unique<Cube2Factory>()));
  ObjectFactoryMap.insert(ObjectFactoryPair(ObjectId::Thorus, std::make_unique<ThorusFactory>()));
}

void PrintHelp()
{
  std::cout << "generator name [params]\n";
  std::cout << "  possible object names and params to use:\n";

  std::for_each(ObjectIdMap.begin(), ObjectIdMap.end(),
    [](std::pair<std::string, ObjectId> item)
      {
        std::cout << "    " << item.first << ", params: " << ParamsHelp[item.second];
        std::cout << "\n";
      });
}

int main(int argc, char* argv[])
{
  if (argc == 1)
  {
    PrintHelp();
    return 0;
  }
  
  InitObjectFactoryMap();
  
  const auto name = argv[1];
  const auto it = ObjectIdMap.find(name);
  
  if (it == ObjectIdMap.end())
    {
      std::cout << "Object not recognized\n";
      return 0;
    }
  
  const auto creatorIt = ObjectFactoryMap.find(it->second);
  
  if (creatorIt == ObjectFactoryMap.end())
  {
      std::cout << "Object creator not found\n";
      return 0;
  }
  
  try {

    Params params;
    for(int i = 2; i < argc; i++)
    {
      params.push_back(argv[i]);
    }

    const auto object3d = creatorIt->second->Create(name, params);

    AmigaFile file;
    file.Save(*object3d);

    object3d->LogVertices();
    object3d->LogFaces();
    
  } catch (const std::out_of_range& ex) {
    std::cout << ex.what() << "\n";
    PrintHelp();
  } catch (const std::bad_cast& ex) {
    std::cout << ex.what() << "\n";
    PrintHelp();
  }
  
  return 0;
  
}

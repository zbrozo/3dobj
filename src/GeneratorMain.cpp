#include "IGenerator.hpp"
#include "Face.hpp"
#include "Object3d.hpp"
#include "Vector3d.hpp"
#include "Cube.hpp"
#include "Cube2.hpp"
#include "Thorus.hpp"
#include "AmigaFile.hpp"

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <array>
#include <map>
#include <memory>
#include <utility>
#include <exception>

const std::string TooLessParamsMessage = "Too less parameters for ";

class IObjectFactory
{
public:
  virtual const Object3D& Create(int argc, char* argv[]) = 0;
};


class ObjectFactory : public IObjectFactory
{
public:

  // factory method
  void Generate(Object3D& object)
  {
    auto& generator = dynamic_cast<IGenerator&>(object);
    generator.Generate();

    object.CreateNormalVectors();
  }
  
};

class CubeFactory : public ObjectFactory
{
public:

  const Object3D& Create(int /*argc*/, char* argv[]) override
  {
    const auto name = argv[1];
    auto object = std::make_unique<Cube>(name);
    Generate(*object);
    return *object.get();
  }
};

class Cube2Factory : public ObjectFactory
{
public:

  const Object3D& Create(int /*argc*/, char* argv[]) override
  {
    const auto name = argv[1];
    auto object = std::make_unique<Cube2>(name);
    Generate(*object);    
    return *object.get();
  }
};

class ThorusFactory : public ObjectFactory
{
public:

  const Object3D& Create(int argc, char* argv[]) override
  {
    const auto name = argv[1];
    if (argc < 4)
    {
      throw std::out_of_range(TooLessParamsMessage + name);
    }
    
    const auto circleSize = argv[2];
    const auto ringSize = argv[3];
    auto object = std::make_unique<Thorus>(
      std::stoi(circleSize), std::stoi(ringSize),
      (std::string(name) + "_" + circleSize + "_" + ringSize).c_str());
    Generate(*object);    
    return *object.get();
  }
};

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

using ObjectCreatorPair = std::pair<ObjectId, std::unique_ptr<IObjectFactory>>;
std::map<ObjectId, std::unique_ptr<IObjectFactory>> ObjectCreatorMap;

void InitObjectCreatorMap()
{
  ObjectCreatorMap.insert(ObjectCreatorPair(ObjectId::Cube, std::make_unique<CubeFactory>()));
  ObjectCreatorMap.insert(ObjectCreatorPair(ObjectId::Cube2, std::make_unique<Cube2Factory>()));
  ObjectCreatorMap.insert(ObjectCreatorPair(ObjectId::Thorus, std::make_unique<ThorusFactory>()));
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
  
  InitObjectCreatorMap();
  
  const auto name = argv[1];
  const auto it = ObjectIdMap.find(name);
  
  if (it == ObjectIdMap.end())
    {
      std::cout << "Object not recognized\n";
      return 0;
    }
  
  const auto creatorIt = ObjectCreatorMap.find(it->second);
  
  if (creatorIt == ObjectCreatorMap.end())
  {
      std::cout << "Object creator not found\n";
      return 0;
  }
  
  try {
    const auto& object3d = creatorIt->second->Create(argc, argv);

    AmigaFile file;
    file.Save(object3d);

    object3d.LogVertices();
    object3d.LogFaces();
    
  } catch (const std::out_of_range& ex) {
    std::cout << ex.what() << "\n";
    PrintHelp();
  } catch (const std::bad_cast& ex) {
    std::cout << ex.what() << "\n";
    PrintHelp();
  }
  
  return 0;
  
}

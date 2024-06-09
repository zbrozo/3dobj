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

class IObjectCreator
{
public:
  virtual const Object3D& Create(int argc, char* argv[]) = 0;
};

class CubeCreator : public IObjectCreator
{
  std::unique_ptr<Cube> object = nullptr;
  
public:

  const Object3D& Create(int /*argc*/, char* argv[]) override
    {
      const auto name = argv[1];
      object = std::make_unique<Cube>(name);

      object->Generate();
      object->LogVertices();
      object->LogFaces();
      object->CreateNormalVectors();

      return *object.get();
    }
};

class Cube2Creator : public IObjectCreator
{
    std::unique_ptr<Cube2> object = nullptr;
  
public:

  const Object3D& Create(int /*argc*/, char* argv[]) override
    {
      const auto name = argv[1];
      object = std::make_unique<Cube2>(name);

      object->Generate();
      object->LogVertices();
      object->LogFaces();
      object->CreateNormalVectors();
      return *object.get();
    }
};

class ThorusCreator : public IObjectCreator
{
    std::unique_ptr<Thorus> object = nullptr;
  
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
      object = std::make_unique<Thorus>(
        std::stoi(circleSize), std::stoi(ringSize),
        (std::string(name) + "_" + circleSize + "_" + ringSize).c_str());
      
      object->Generate();
      object->LogVertices();
      object->LogFaces();
      object->CreateNormalVectors();
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

using ObjectCreatorPair = std::pair<ObjectId, std::unique_ptr<IObjectCreator>>;
std::map<ObjectId, std::unique_ptr<IObjectCreator>> ObjectCreatorMap;

void InitObjectCreatorMap()
{
  ObjectCreatorMap.insert(ObjectCreatorPair(ObjectId::Cube, std::make_unique<CubeCreator>()));
  ObjectCreatorMap.insert(ObjectCreatorPair(ObjectId::Cube2, std::make_unique<Cube2Creator>()));
  ObjectCreatorMap.insert(ObjectCreatorPair(ObjectId::Thorus, std::make_unique<ThorusCreator>()));
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
    
  } catch (const std::out_of_range& ex) {
    std::cout << ex.what();
  }

  return 0;
  
}

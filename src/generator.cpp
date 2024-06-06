
#include "face.hpp"
#include "vector3d.hpp"
#include "cube.hpp"
#include "cube2.hpp"
#include "thorus.hpp"
#include "amigafile.hpp"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <array>
#include <map>
#include <memory>

enum class ObjectId {
  None = 0,
  Cube = 1,
  Cube2 = 2,
  Thorus = 3
};

std::map<std::string, ObjectId> Objects {
  {"cube", ObjectId::Cube},
  {"cube2", ObjectId::Cube2},
  {"thorus", ObjectId::Thorus}
};

std::map<ObjectId, std::string> ParamsHelp {
  {ObjectId::Cube, ""},
  {ObjectId::Cube2, ""},
  {ObjectId::Thorus, "thorusCircleSize thorusRingSize"}
};

const std::string TooLessParamsMessage = "Too less parameters for ";

void PrintHelp()
{
  std::cout << "generator name [params]\n";
  std::cout << "  possible object names and params to use:\n";

  std::for_each(Objects.begin(), Objects.end(),
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

  const auto name = argv[1];

  const auto it = Objects.find(name);
  
  if (it == Objects.end())
    {
      std::cout << "Object not recognized\n";
      return 0;
    }
  
  std::unique_ptr<Object3D> object = nullptr;
  
  switch(it->second)
    {
    case ObjectId::Cube:
      {
        object = std::make_unique<Cube>(name);
        break;
      }

    case ObjectId::Cube2:
      {
        object = std::make_unique<Cube2>(name);
        break;
      }

    case ObjectId::Thorus:
      {
        if (argc < 4)
        {
            std::cout << TooLessParamsMessage << name << "\n";
            PrintHelp();
            return 0;
          }
        
        const auto circleSize = argv[2];
        const auto ringSize = argv[3];
        
        object = std::make_unique<Thorus>(
          std::stoi(circleSize),
          std::stoi(ringSize),
          (std::string(name) + "_" + circleSize + "_" + ringSize).c_str());
        
        break;
      }
    default:
      break;
    }

  if (object == nullptr)
    {
      std::cout << "No object created\n";
      return 0;
    }
 
  object->Generate();
  object->LogVertices();
  object->LogFaces();
  object->CreateNormalVectors();
  
  AmigaFile file;
  file.Save(*object);

  return 0;
  
}

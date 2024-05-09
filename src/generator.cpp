
#include "face.hpp"
#include "vector3d.hpp"
#include "cube.hpp"
#include "cube2.hpp"
#include "thorus.hpp"
#include "amigafile.hpp"
#include <cstddef>
#include <iostream>
#include <array>
#include <map>

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

int main(int argc, char* argv[])
{
  if (argc == 1)
    {
      std::cout << "No parameters\n";
      return 0;
    }

  const auto name = argv[1];

  const auto it = Objects.find(name);
  
  if (it == Objects.end())
    {
      std::cout << "Object not recognized\n";
      return 0;
    }
  
  Object3D* object = nullptr;
  
  switch(it->second)
    {
    case ObjectId::Cube:
      {
        object = new Cube("cube");
        break;
      }

    case ObjectId::Cube2:
      {
        object = new Cube("cube2");
        break;
      }

    case ObjectId::Thorus:
      {
        if (argc < 4)
          {
            std::cout << "Too less parameters for thorus\n";
            return 0;
          }
        
        const auto circleSize = argv[2];
        const auto ringSize = argv[3];
        
        object = new Thorus(std::stoi(circleSize),
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

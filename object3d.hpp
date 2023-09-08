#pragma once
#include <vector>
#include <string>
#include "vertex.hpp"

using Face = std::vector<unsigned short>;
using Faces = std::vector<Face>;

class Object3D
{
  std::string name;
  
public:

  Object3D(const char* _name) :
    name(_name)
  {
  }
  
  Vertices vertices;
  Faces faces;

  Vertices normalVectorsInFaces;
  Vertices normalVectorsInVertices;

  void CreateNormalVectors();
  
  bool SaveToFile();

  void LogVertices();
  void LogFaces();


  
};

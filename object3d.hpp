#pragma once

#include <vector>
#include <string>

#include "vector3d.hpp"
#include "vertex.hpp"
#include "face.hpp"

//class Face;
//class Vector3d;
//class Vertex;

using Vertices = std::vector<Vertex>;
using Faces = std::vector<Face>;
using Vectors = std::vector<Vector3d>;

using FaceNumbers = std::vector<unsigned short>;
using FaceNumbersInVertices = std::vector<FaceNumbers>;

class Object3D
{
  std::string mName;
  
public:

  Object3D(const char* name) :
    mName(name)
  {
  }
  
  Vertices mVertices;
  Faces mFaces;
  Vectors mNormalVectorsInFaces;
  Vectors mNormalVectorsInVertices;

  void CreateNormalVectors();
  
  bool SaveToFile();

  void LogVertices();
  void LogFaces();
  
};

#pragma once

#include <vector>
#include <string>
#include <utility>

#include "vector3d.hpp"
#include "vertex.hpp"
#include "face.hpp"
#include "vertices.hpp"

//class Face;
//class Vector3d;
//class Vertex;

//using Vertices = std::vector<Vertex>;
using Faces = std::vector<Face>;
using Vectors = std::vector<Vector3d>;

using FaceNumbers = std::vector<unsigned short>;
using FaceNumbersInVertices = std::vector<FaceNumbers>;

class Object3D
{
  
public:

  Object3D(const char* name) :
    mName(name)
  {
  }
  
  std::string mName;
  Vertices mVertices;
  Faces mFaces;
  Vectors mNormalVectorsInFaces;
  Vectors mNormalVectorsInVertices;

  void CreateNormalVectors();
  void LogVertices();
  void LogFaces();
  
  virtual void Generate() = 0;

  static std::pair<Face, Vertices> Merge(const Vertices& objectVertices,
                                         const Face& face,
                                         const Vertices& vertices);
};

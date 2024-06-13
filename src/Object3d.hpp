#pragma once

#include <vector>
#include <string>
#include <utility>

#include "Vector3d.hpp"
#include "Vertex.hpp"
#include "Face.hpp"
#include "Vertices.hpp"

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

  virtual ~Object3D() = default;

  Object3D(Object3D const &) = delete;
  Object3D(Object3D &&) = default;
  Object3D& operator=(Object3D const &) = delete;
  Object3D& operator=(Object3D &&) = delete;
  
  std::string mName;
  Vertices mVertices;
  Faces mFaces;
  Vectors mNormalVectorsInFaces;
  Vectors mNormalVectorsInVertices;

  void CreateNormalVectors();
  
  void LogVertices() const;
  void LogFaces() const;
  
  static std::pair<Face, Vertices> Merge(const Vertices& objectVertices,
                                         const Face& face,
                                         const Vertices& vertices);
};

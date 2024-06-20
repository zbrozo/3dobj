#pragma once

#include <vector>
#include <string>
#include <utility>
#include "Face.hpp"
#include "Vertices.hpp"
#include "Types.hpp"

using Faces = std::vector<Face>;
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
  Object3D(Object3D &&) = delete;
  Object3D& operator=(Object3D const &) = delete;
  Object3D& operator=(Object3D &&) = delete;
  
  std::string mName;
  Vertices mVertices;
  Faces mFaces;
  Vectors mNormalVectorsInFaces;
  Vectors mNormalVectorsInVertices;

  int GetFacesQuantity() const
  {
    return mFaces.size();
  }

  int GetVerticesQuantity() const
  {
    return mVertices.size();
  }
  
  void CreateNormalVectors();
  
  void LogVertices() const;
  void LogFaces() const;
  
  static std::pair<Face, Vertices> Merge(const Vertices& objectVertices,
                                         const Face& face,
                                         const Vertices& vertices);
};

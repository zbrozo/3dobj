#include <iostream>
#include <algorithm>
#include <cmath>
#include "object3d.hpp"
#include "vector3d.hpp"

namespace
{
  
auto PrepareFacesAssignedToVertices(const Vertices& vertices,
                                    const Faces& faces)
{
  std::cout << __FUNCTION__ << "\n";

  FaceNumbersInVertices result;
  
  for(unsigned int i = 0; i < vertices.size(); i++)
    {
      FaceNumbers foundFaceNumbers;

      unsigned short faceNr = 0;
      
      for (auto face : faces)
        {
          if (std::find(face.begin(), face.end(), i) != face.end())
          {
            foundFaceNumbers.push_back(faceNr);
          }
          
          ++faceNr;
        }

      result.push_back(foundFaceNumbers);

      for(auto v : foundFaceNumbers)
        {
          std::cout << v << ", ";
        }
      std::cout << "\n";
      
    }

  return result;
}

auto CalculateNormalVectorToFaces(const Vertices& vertices,
                                  const Faces& faces
                                  )
{
  Vectors normalVectors;
  for(auto face : faces)
    {
      const auto vector = face.CalculateNormalVector(vertices);
      normalVectors.push_back(vector);
    }

  return normalVectors;
}

auto CalculateVectorsInVertices(const FaceNumbersInVertices& vertexInFaceDependency,
                                const Vectors& normalFaceVectors)
{
  std::cout << __FUNCTION__ << "\n";

  Vectors vectorsInVertices;
  
  for(auto faces : vertexInFaceDependency)
    {
      short x = 0;
      short y = 0;
      short z = 0;
      
      for(auto faceNr : faces)
        {
          std::cout << "face: " <<  faceNr << ", " << x << "\n";
          
          x += normalFaceVectors[faceNr].mX;
          y += normalFaceVectors[faceNr].mY;
          z += normalFaceVectors[faceNr].mZ;
        }

      const short count = faces.size();
      
      if (faces.size() != 0)
        {
          x = x / count;
          y = y / count;
          z = z / count;
        }

      Vertex vertex(x, y, z);
      std::cout << x << ", " << y << ", " << z << "\n";
      
      vectorsInVertices.push_back(Vector3d(vertex));      
    }

  return vectorsInVertices;
}

auto NormalizeVectorsInVertices(const Vectors& vectorsInVertices)
{
  std::cout << __FUNCTION__ << "\n";

  Vectors normalizedVectorsInVertices;

  for (auto vector : vectorsInVertices)
    {
      normalizedVectorsInVertices.push_back(vector.Normalize());
    }

  return normalizedVectorsInVertices;
}

}

void Object3D::CreateNormalVectors()
{
  FaceNumbersInVertices facesAssignedToVertex = PrepareFacesAssignedToVertices(mVertices, mFaces);
  
  mNormalVectorsInFaces = CalculateNormalVectorToFaces(mVertices, mFaces);

  Vectors vectorsInVertices = CalculateVectorsInVertices(facesAssignedToVertex, mNormalVectorsInFaces);

  mNormalVectorsInVertices = NormalizeVectorsInVertices(vectorsInVertices);
}
    
void Object3D::LogVertices()
{
  std::cout << __FUNCTION__ << "\n";
  for (auto v : mVertices)
    {
      std::cout << v.ToString() << "\n";
    }
}

void Object3D::LogFaces()
{
  std::cout << __FUNCTION__ << "\n";
  for (auto face : mFaces)
    {
      std::cout << face.ToString() << "\n";
    }
}


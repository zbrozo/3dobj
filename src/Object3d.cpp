#include <iostream>
#include <algorithm>
#include <cmath>

#include "Object3d.hpp"
#include "Vector3d.hpp"

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
    
void Object3D::LogVertices() const
{
  std::cout << __FUNCTION__ << "\n";
  for (auto v : mVertices)
    {
      std::cout << v.ToString() << "\n";
    }
}

void Object3D::LogFaces() const
{
  std::cout << __FUNCTION__ << "\n";
  for (auto face : mFaces)
    {
      std::cout << face.ToString() << "\n";
    }
}

std::pair<Face, Vertices> Object3D::Merge(const Vertices& objectVertices,
                                          const Face& face,
                                          const Vertices& vertices)
{
  Face resultFace;
  Vertices resultVertices = objectVertices;
  
  for (size_t i = 0; i < face.size(); ++i)
    {
      auto vertexNr = face[i];
      Vertex vertex = vertices[vertexNr];

      int foundNr = 0;

      auto found = std::find_if(resultVertices.begin(), resultVertices.end(), [&](const Vertex& v){
        const short vertexRange = 0;

        if ((vertex.mX >= v.mX - vertexRange && vertex.mX <= v.mX + vertexRange)
            && (vertex.mY >= v.mY - vertexRange && vertex.mY <= v.mY + vertexRange)
            && (vertex.mZ >= v.mZ - vertexRange && vertex.mZ <= v.mZ + vertexRange))
          {
            return true;
          }
        
        ++foundNr;
        return false;
      });

      if (found != resultVertices.end())
        {
          resultFace.push_back(foundNr);
        }
      else
        {
          const short nr = resultVertices.size();
          
          resultFace.push_back(nr);
          resultVertices.push_back(vertex);
        }
    }
  
  return std::make_pair(resultFace, resultVertices);
}
